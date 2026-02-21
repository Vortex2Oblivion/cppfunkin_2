#include "PlayScene.hpp"

#include "NoteLane.hpp"
#include "PlayField.hpp"
#include "Sprite.hpp"

namespace funkin::scenes {
	PlayScene::PlayScene() = default;
	PlayScene::~PlayScene() = default;

	void PlayScene::create() {
		Scene::create();

		inst = LoadMusicStream("assets/songs/bopeebo/Inst.ogg");
		voices = LoadMusicStream("assets/songs/bopeebo/Voices-opponent.ogg");
		voicesPlayer = LoadMusicStream("assets/songs/bopeebo/Voices-player.ogg");

		std::vector<Music> tracks = {inst, voices, voicesPlayer};

		conductor = std::make_shared<Conductor>(tracks);
		conductor->bpm = 110.0f;
		conductor->start();

		const auto test = std::make_shared<Sprite>(100, 150);
		test->loadTexture("assets/images/noteskins/funkin/NOTE_hold_assets.png");
		add(test);

		auto song = data::Song::parseSong("bopeebo");

		const auto lane = std::make_shared<PlayField>(100.0f, 100.0f, 4, song.speed, song.notes, conductor);
		add(lane);
	}

	void PlayScene::update(const float delta) {
		Scene::update(delta);
		conductor->update(delta);
	}
}
