#include "PlayScene.hpp"

#include "Sprite.hpp"
#include "objects/notes/PlayField.hpp"

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

		henry = std::make_shared<Sprite>(300, -300);
		henry->loadTexture("assets/characters/henry/spritesheet.png");
		henry->animation.loadSparrow("assets/characters/henry/spritesheet.xml");
		henry->animation.addByPrefix("idle", "idle0");
		henry->animation.play("idle");
		add(henry);

		const auto opponentField = std::make_shared<objects::notes::PlayField>(100.0f, 100.0f, 4, song.speed, song.opponentNotes,
		                                                                       conductor);
		add(opponentField);

		const auto playerField = std::make_shared<objects::notes::PlayField>(static_cast<float>(GetRenderWidth()) / 2 + 100.0f, 100.0f,
		                                                                     4, song.speed, song.playerNotes, conductor);
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
