#include "PlayScene.hpp"

#include <iostream>

#include "MainMenuScene.hpp"
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
	PlayScene::PlayScene(const std::string &songName) { this->songName = songName; };

	PlayScene::~PlayScene() {
		scripts.clear();
		events.clear();
	};

	void PlayScene::create() {
		Scene::create();

		for (const auto &file: std::filesystem::directory_iterator("assets/songs/" + songName)) {
			auto fileString = file.path().string();
			if (fileString.ends_with(".lua")) {
				scripts.push_back(std::make_shared<modding::LuaScript>(fileString));
			}
		}

		camHUD = std::make_shared<Camera>();
		Game::cameras.push_back(camHUD);

		setOnScripts("camHUD", camHUD);

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

		setOnScripts("conductor", conductor);

		girlfriend = std::make_shared<objects::Character>(0, 0, songData.spectator, objects::CharacterType::GIRLFRIEND);
		scripts.push_back(girlfriend->script);

		boyfriend = std::make_shared<objects::Character>(0, 0, songData.player, objects::CharacterType::BOYFRIEND);
		scripts.push_back(boyfriend->script);

		dad = std::make_shared<objects::Character>(0, 0, songData.opponent, objects::CharacterType::DAD);
		scripts.push_back(dad->script);

		stage = std::make_shared<objects::Stage>(songData.stage, boyfriend, dad, girlfriend);
		add(stage);
		scripts.push_back(stage->script);

		defaultZoom = Game::defaultCamera->zoom;

		scoreText = std::make_shared<Text>(0, GetRenderHeight() - 55, "Score: 0 | Misses: 0 | Accuracy: 100.00%");
		scoreText->camera = camHUD;
		scoreText->borderSize = 2.0f;
		scoreText->size = 20.0f;
		scoreText->loadFont("assets/fonts/vcr.ttf");
		scoreText->screenCenter(math::Axes::X);

		healthBar = std::make_shared<objects::HealthBar>(0, scoreText->position.y - 30, dad->barColor, boyfriend->barColor,
														 songData.opponent, songData.player);
		healthBar->camera = camHUD;
		healthBar->position.x = (static_cast<float>(GetRenderWidth()) - healthBar->bar->hitbox.width) / 2.0f;
		add(healthBar);

		add(scoreText);

		const std::array<std::string, 4> ratings = {"sick", "good", "bad", "shit"};

		for (const auto &rating: ratings) {
			Sprite::precacheTexture("assets/images/" + rating + ".png");
		}

		for (uint8_t i = 0; i < 10; i++) {
			Sprite::precacheTexture("assets/images/num" + std::to_string(i) + ".png");
		}

		comboGroup = std::make_shared<Group<Sprite>>();
		comboGroup->camera = camHUD;
		add(comboGroup);

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

		setOnScripts("opponentField", opponentField);


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
				healthBar->bar->progress = playerField->health;

				if (!note->sustainNote) {

					std::vector<std::string> seperatedScore = utilities::CoolUtil::split(std::to_string(playerField->combo), "");
					std::ranges::reverse(seperatedScore);

					uint8_t loop = 1;

					for (const auto &digit: seperatedScore) {
						auto comboSpr = std::make_shared<Sprite>(GetRenderWidth() * 0.507 - 36 * loop - 65, GetRenderHeight() * 0.44);
						comboSpr->loadTexture("assets/images/num" + digit + ".png");

						comboSpr->acceleration.y = static_cast<float>(GetRandomValue(250, 300));
						comboSpr->velocity.y -= static_cast<float>(GetRandomValue(130, 150));
						comboSpr->velocity.x = static_cast<float>(GetRandomValue(-5, 5));

						comboGroup->add(comboSpr);

						// my REALLY stupid solution until i make a custom timer system lol
						Raytween::Value(0, 0, conductor->crochet / 1000.0f, EASE_LINEAR)->SetOnComplete([comboSpr, this] {
							Raytween::Value(comboSpr->alpha, 0.0f, 0.2, EASE_LINEAR)
									->SetOnUpdate([comboSpr](const float value) { comboSpr->alpha = value; })
									->SetOnComplete([comboSpr, this] { comboGroup->remove(comboSpr); });
						});
						loop++;
					}


					std::string ratingStr = "shit";
					auto noteTime = abs(note->strumTime - conductor->time);
					if (noteTime <= 45.0f) {
						ratingStr = "sick";
					} else if (noteTime <= 65.0f) {
						ratingStr = "good";
					} else if (noteTime <= 100.0f) {
						ratingStr = "bad";
					}

					const auto ratingSpr = std::make_shared<Sprite>(GetRenderWidth() * 0.474, GetRenderHeight() * 0.45 - 60);
					ratingSpr->loadTexture("assets/images/" + ratingStr + ".png");
					ratingSpr->position.x -= ratingSpr->hitbox.width / 2.0f;
					ratingSpr->position.y -= ratingSpr->hitbox.height / 2.0f;
					ratingSpr->acceleration.y = 550.0f;
					ratingSpr->acceleration.y = static_cast<float>(GetRandomValue(250, 300));
					ratingSpr->velocity.y -= static_cast<float>(GetRandomValue(130, 150));
					ratingSpr->velocity.x = static_cast<float>(GetRandomValue(-5, 5));
					comboGroup->add(ratingSpr);

					Raytween::Value(0, 0, conductor->crochet / 1000.0f, EASE_LINEAR)->SetOnComplete([ratingSpr, this] {
						Raytween::Value(ratingSpr->alpha, 0.0f, 0.2, EASE_LINEAR)
								->SetOnUpdate([ratingSpr](const float value) { ratingSpr->alpha = value; })
								->SetOnComplete([ratingSpr, this] { comboGroup->remove(ratingSpr); });
					});
				}
			});
			lane->onNoteMiss.append([this](const auto &note) {
				updateScoreText();
				healthBar->bar->progress = playerField->health;
			});
		}

		setOnScripts("playerField", playerField);

		conductor->start();
		conductor->onBeatHit.append([this](const auto beat) {
			if (beat % boyfriend->danceEvery == 0) {
				if (boyfriend->canDance(conductor->stepCrochet)) {
					boyfriend->dance();
				}
			}

			if (beat % dad->danceEvery == 0) {
				if (dad->canDance(conductor->stepCrochet)) {
					dad->dance();
				}
			}

			if (beat % girlfriend->danceEvery == 0) {
				if (girlfriend->canDance(conductor->stepCrochet)) {
					girlfriend->dance();
				}
			}

			healthBar->bumpIcons();

			constexpr float maxZoom = 1.35f;

			if (!easingCameraZoom && Game::defaultCamera->zoom < maxZoom * defaultZoom && beat % 4 == 0) {
				Game::defaultCamera->zoom += zoomIntensity * defaultZoom;
			}

			if (camHUD->zoom < maxZoom * defaultHUDZoom && beat % 4 == 0) {
				camHUD->zoom += hudZoomIntensity * defaultHUDZoom;
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
		} else if (IsKeyPressed(KEY_ENTER)) {
			Game::switchScene(std::make_unique<MainMenuScene>());
		}

		constexpr float decayRate = 0.95f;
		const float dt = 60.0f * delta;

		Game::defaultCamera->zoom = Lerp(defaultZoom, Game::defaultCamera->zoom, pow(decayRate, dt));
		camHUD->zoom = Lerp(defaultHUDZoom, camHUD->zoom, pow(decayRate, dt));


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
						->SetOnUpdate([this](const float value) {
							easingCameraZoom = true;
							defaultZoom = Game::defaultCamera->zoom = value;
						})
						->SetOnComplete([this] { easingCameraZoom = false; });

			} else if (event.name == "FocusCamera") {
				Vector2 target = Vector2Zero();

				const auto targetObject =
						static_cast<events::CameraTarget>(event.parameters.contains("char") ? event.parameters["char"] : event.parameters);

				switch (targetObject) {
					case events::CameraTarget::GIRLFRIEND:
						target = girlfriend->getMidpoint() + girlfriend->cameraOffset;
						break;
					case events::CameraTarget::BOYFRIEND:
						target = boyfriend->getMidpoint() - Vector2{.x = 100.0f, .y = 100.0f} + boyfriend->cameraOffset;
						break;
					case events::CameraTarget::DAD:
						target = dad->getMidpoint() + Vector2{.x = 150.0f, .y = -100.0f} + dad->cameraOffset;
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
		scoreText->setText(TextFormat("Score: %d | Misses: %d | Accuracy: %.2f%%", playerField->getScore(), playerField->getMisses(),
									  playerField->accuracy));
		scoreText->screenCenter(math::Axes::X);
	}
} // namespace funkin::scenes
