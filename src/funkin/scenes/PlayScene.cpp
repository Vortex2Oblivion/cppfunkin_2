#include "PlayScene.hpp"

#include "NoteLane.hpp"
#include "Sprite.hpp"

namespace funkin::scenes {
	PlayScene::PlayScene() = default;
	PlayScene::~PlayScene() = default;

	void PlayScene::create() {
		Scene::create();

		inst = LoadMusicStream("assets/songs/titular/Inst.ogg");
		voices = LoadMusicStream("assets/songs/titular/Voices-opponent.ogg");
		voicesPlayer = LoadMusicStream("assets/songs/titular/Voices-player.ogg");

		std::vector<Music> tracks = {inst, voices, voicesPlayer};

		conductor = std::make_shared<Conductor>(tracks);
		conductor->bpm = 110.0f;
		conductor->start();

		const auto test = std::make_shared<Sprite>(100, 150);
		test->loadTexture("assets/images/noteskins/funkin/NOTE_hold_assets.png");
		add(test);

		auto song = data::Song::parseSong("titular");

		const auto lane = std::make_shared<NoteLane>(100, 100, song.notes, conductor);
		lane->speed = song.speed;
		add(lane);
	}

	void PlayScene::update(const float delta) {
		Scene::update(delta);
		conductor->update(delta);
	}
}
