#include "PlayScene.hpp"

#include "Sprite.hpp"

namespace funkin::scenes {
	PlayScene::PlayScene() = default;
	PlayScene::~PlayScene() = default;

	void PlayScene::create() {
		Scene::create();

		inst = LoadMusicStream("assets/songs/titular/Inst.ogg");
		voices = LoadMusicStream("assets/songs/titular/Voices-opponent.ogg");
		voicesPlayer = LoadMusicStream("assets/songs/titular/Voices-player.ogg");
		conductor = Conductor({inst, voices, voicesPlayer});
		conductor.bpm = 110.0f;
		conductor.start();

		const auto test = std::make_shared<Sprite>(100, 150);
		test->loadTexture("assets/images/noteskins/funkin/NOTE_hold_assets.png");
		add(test);
	}

	void PlayScene::update(const float delta) {
		Scene::update(delta);
		conductor.update(delta);
	}
}
