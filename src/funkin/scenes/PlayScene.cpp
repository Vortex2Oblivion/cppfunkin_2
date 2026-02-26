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

		const std::string songName = "titular";

		inst = LoadMusicStream(("assets/songs/" + songName + "/Inst.ogg").c_str());
		voices = LoadMusicStream(("assets/songs/" + songName + "/Voices-opponent.ogg").c_str());
		voicesPlayer = LoadMusicStream(("assets/songs/" + songName + "/Voices-player.ogg").c_str());

		std::vector<Music> tracks = {inst, voices, voicesPlayer};

		conductor = std::make_shared<Conductor>(tracks);
		conductor->bpm = 110.0f;
		conductor->start();

		auto song = data::Song::parseSong(songName);

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
		add(opponentField);

		const auto playerField = std::make_shared<objects::notes::PlayField>(static_cast<float>(GetRenderWidth()) / 2 + 100.0f, 50.0f, 4, song.speed, song.playerNotes, conductor);
		add(playerField);

		lua_State *L = luaL_newstate();  // Create a new Lua state
		luaL_openlibs(L);                 // Load Lua libraries
		luaaa::LuaClass<Sprite> luaSprite(L, "Sprite");
		luaSprite.ctor<float, float>();
		luaSprite.fun("loadTexture", &Sprite::loadTexture);
		luaSprite.fun("draw", &Sprite::draw);
		luaSprite.fun("update", &Sprite::update);
		luaaa::LuaModule(L).fun("add", &Game::add);
		luaL_dofile(L, "assets/scripts/testscript.lua"); // Execute Lua script
		//lua_close(L);                     // Close the Lua state
	}

	void PlayScene::update(const float delta) {
		Scene::update(delta);
		conductor->update(delta);
		if (IsKeyPressed(KEY_SPACE)) {
			henry->animation.play("idle");
		}
	}
}
