#include "PlayScene.hpp"

#include "Sprite.hpp"

namespace funkin::scenes {
	PlayScene::PlayScene() = default;
	PlayScene::~PlayScene() = default;

	void PlayScene::create() {
		Scene::create();

		inst = LoadMusicStream("assets/songs/titular/Inst.ogg");
		conductor = Conductor({inst});
		conductor.bpm = 110.0f;
		conductor.start();

		const auto test = std::make_shared<Sprite>(100, 150);
		add(test);
	}

	void PlayScene::update(const float delta) {
		Scene::update(delta);
		conductor.update(delta);
	}
}
