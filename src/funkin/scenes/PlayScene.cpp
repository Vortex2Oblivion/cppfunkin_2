#include "PlayScene.hpp"

#include "Sprite.hpp"


namespace funkin::scenes {
	PlayScene::PlayScene() = default;
	PlayScene::~PlayScene() = default;

	void PlayScene::create() {
		Scene::create();
		const auto test = Sprite(100, 100);
		add(test);
	}
}
