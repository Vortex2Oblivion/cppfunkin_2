#include "PlayScene.hpp"

#include <iostream>

#include "Game.hpp"
#include "Sprite.hpp"
#include "objects/notes/PlayField.hpp"
#include "luaaa.hpp"

namespace funkin::scenes {
	PlayScene::PlayScene() = default;

	PlayScene::~PlayScene() = default;

	std::shared_ptr<Sprite> henry;

	void PlayScene::create() {
		Scene::create();

		camHUD = std::make_shared<Camera>();
		Game::cameras.push_back(camHUD);

		Game::defaultCamera->zoom = 0.7f;

		const std::string songName = "titular";

		inst = LoadMusicStream(("assets/songs/" + songName + "/Inst.ogg").c_str());
		voices = LoadMusicStream(("assets/songs/" + songName + "/Voices-opponent.ogg").c_str());
		voicesPlayer = LoadMusicStream(("assets/songs/" + songName + "/Voices-player.ogg").c_str());

		std::vector tracks = {inst, voices, voicesPlayer};

		conductor = std::make_shared<Conductor>(tracks);
		conductor->bpm = 110.0f;
		conductor->start();

		auto song = data::Song::parseSong(songName);

		const auto script = std::make_shared<modding::LuaScript>("assets/stages/desert/stage.lua");
		scripts.push_back(script);

		henry = std::make_shared<Sprite>(300, 0);
		henry->loadTexture("assets/characters/henry/spritesheet.png");
		henry->animation.loadSparrow("assets/characters/henry/spritesheet.xml");
		henry->animation.addByPrefix("idle", "idle");
		henry->animation.play("idle");
		add(henry);

		const auto opponentField = std::make_shared<objects::notes::PlayField>(100.0f, 50.0f, 4, song.speed, song.opponentNotes,conductor);
		for (const auto& lane : opponentField->members) {
			lane->botplay = true;
		}
		opponentField->camera = camHUD;
		add(opponentField);

		const auto playerField = std::make_shared<objects::notes::PlayField>(static_cast<float>(GetRenderWidth()) / 2 + 100.0f, 50.0f, 4, song.speed, song.playerNotes, conductor);
		playerField->camera = camHUD;
		add(playerField);
	}

	void PlayScene::update(const float delta) {
		Scene::update(delta);
		conductor->update(delta);
		if (IsKeyPressed(KEY_SPACE)) {
			henry->animation.play("idle");
		}

	}
}
