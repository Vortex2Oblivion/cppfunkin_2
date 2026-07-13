#include "PlayScene.hpp"

#include "funkin/Game.hpp"
#include "funkin/Scene.hpp"
#include "funkin/data/Song.hpp"
#include "funkin/game/Conductor.hpp"
#include "funkin/game/events/CameraTarget.hpp"
#include "funkin/objects/Character.hpp"
#include "funkin/objects/Stage.hpp"
#include "funkin/objects/notes/PlayField.hpp"
#include "funkin/utilities/CoolUtil.hpp"
#include "raytween.h"

namespace funkin::scenes {
	PlayScene::PlayScene() = default;

	PlayScene::~PlayScene() { scripts.clear(); };

	void PlayScene::create() {
		Scene::create();

		camHUD = std::make_shared<Camera>();
		Game::cameras.push_back(camHUD);

		songName = "darnell bf mix";
		songData = data::Song::parseSong(songName, "hard");
		events = songData.events;

		inst = LoadMusicStream(("assets/songs/" + songName + "/Inst.ogg").c_str());
		const std::string voicesPlayerPath = FileExists(("assets/songs/" + songName + "/Voices-player.ogg").c_str())
													 ? ("assets/songs/" + songName + "/Voices-player.ogg").c_str()
													 : ("assets/songs/" + songName + "/Voices.ogg").c_str();
		voicesPlayer = LoadMusicStream(voicesPlayerPath.c_str());
		voices = LoadMusicStream(("assets/songs/" + songName + "/Voices-opponent.ogg").c_str());

		tracks = {inst, voices, voicesPlayer};

		conductor = std::make_shared<Conductor>(tracks);
		conductor->bpm = songData.bpm;

		boyfriend = std::make_shared<objects::Character>(0, 0, songData.player, objects::CharacterType::BOYFRIEND);
		scripts.push_back(boyfriend->script);

		dad = std::make_shared<objects::Character>(0, 0, songData.opponent, objects::CharacterType::DAD);
		scripts.push_back(dad->script);

		stage = std::make_shared<objects::Stage>(songData.stage, boyfriend, dad);
		add(stage);
		scripts.push_back(stage->script);

		scoreText = std::make_shared<Text>(0, GetRenderHeight() - 65, "Score: 0 | Misses: 0 | Accuracy: 100.00%");
		scoreText->camera = camHUD;
		scoreText->loadFont("assets/fonts/vcr.ttf");
		scoreText->borderSize = 2.0f;
		scoreText->screenCenter(math::Axes::X);
		add(scoreText);

		opponentField = std::make_shared<objects::notes::PlayField>(100.0f, 50.0f, 4, songData.speed, songData.opponentNotes, conductor);
		opponentField->setBotplay(true);
		opponentField->camera = camHUD;
		add(opponentField);

		for (const auto &lane: opponentField->members) {
			lane->onNoteHit.append([this](const auto &note) {
				std::array<std::string, 4> anims = {"singLEFT", "singDOWN", "singUP", "singRIGHT"};
				if (!(note->sustainNote && dad->getCurrentAnimation()->currentFrame <= 2) ||
					!dad->getCurrentAnimation()->name.starts_with("sing")) {
					dad->animation.play(anims[note->lane % 4], true);
					if (!note->sustainNote) {
						dad->holdTimer = 0.0f;
					}
				}
			});
		}


		playerField = std::make_shared<objects::notes::PlayField>(static_cast<float>(GetRenderWidth()) / 2 + 100.0f, 50.0f, 4,
																  songData.speed, songData.playerNotes, conductor);
		playerField->camera = camHUD;
		add(playerField);

		for (const auto &lane: playerField->members) {
			lane->onNoteHit.append([this](const auto &note) {
				std::array<std::string, 4> anims = {"singLEFT", "singDOWN", "singUP", "singRIGHT"};

				if (!(note->sustainNote && boyfriend->getCurrentAnimation()->currentFrame <= 2) ||
					!boyfriend->getCurrentAnimation()->name.starts_with("sing")) {
					boyfriend->animation.play(anims[note->lane % 4], true);

					if (!note->sustainNote) {
						boyfriend->holdTimer = 0.0f;
					}
				}
				updateScoreText();
			});
			lane->onNoteMiss.append([this](const auto& note) {
				updateScoreText();
			});
		}

		conductor->start();
		conductor->onBeatHit.append([this](const auto &beat) {
			if (beat % boyfriend->danceEvery == 0) {
				if (boyfriend->canDance(conductor->stepCrochet)) {
					boyfriend->animation.play("idle");
					boyfriend->holdTimer = 0.0f;
				}
			}

			if (beat % dad->danceEvery == 0) {
				if (dad->canDance(conductor->stepCrochet)) {
					dad->animation.play("idle");
					dad->holdTimer = 0.0f;
				}
			}
		});

		callOnScripts("onCreatePost");
	}

	void PlayScene::update(const float delta) {
		callOnScripts("onUpdate", delta);

		Scene::update(delta);

		conductor->update(delta);

		if (IsKeyPressed(KEY_SPACE)) {
			if (conductor->playing) {
				conductor->pause();
			} else {
				conductor->resume();
			}
		}

		while (!events.empty() && events.front().time <= conductor->time) {
			auto event = events.front();
			if (event.name == "ZoomCamera") {

				const float zoom =
						event.parameters.contains("zoom") ? static_cast<float>(event.parameters["zoom"]) : Game::defaultCamera->zoom;
				const float duration = event.parameters.contains("duration") ? static_cast<float>(event.parameters["duration"]) : 0.0f;
				const std::string ease =
						event.parameters.contains("easeDir")
								? static_cast<std::string>(event.parameters["ease"]) + static_cast<std::string>(event.parameters["easeDir"])
								: static_cast<std::string>(event.parameters["ease"]);


				Raytween::Value(Game::defaultCamera->zoom, zoom, conductor->stepCrochet / 1000.0f * duration,
								utilities::CoolUtil::easeFromString(ease))
						->SetOnUpdate([](const float value) { Game::defaultCamera->zoom = value; });
			} else if (event.name == "FocusCamera") {
				Vector2 target = Vector2Zero();
				const auto targetObject =
						static_cast<events::CameraTarget>(event.parameters.contains("char") ? event.parameters["char"] : event.parameters);
				switch (targetObject) {
					case events::CameraTarget::BOYFRIEND:
						target = boyfriend->getMidpoint() - Vector2{.x = 100.0f, .y = 100.0f};
						break;
					case events::CameraTarget::DAD:
						target = dad->getMidpoint() + Vector2{.x = 150.0f, .y = -100.0f};
						break;
					default:
						break;
				}
				Game::defaultCamera->follow = target;
			}
			callOnScripts("onEvent", events.front().name);
			events.erase(events.begin());
		}

		callOnScripts("onUpdatePost", delta);
	}

	void PlayScene::updateScoreText() const {
		scoreText->setText(TextFormat("Score: %d | Misses: %d | Accuracy: %.2f%%", playerField->getScore(),
													  playerField->getMisses(), playerField->getAccuracy()));
		scoreText->screenCenter(math::Axes::X);
	}
} // namespace funkin::scenes
