#include "PlayScene.hpp"

#include "Sprite.hpp"

namespace funkin::scenes {
	PlayScene::PlayScene() {
		auto test = std::make_shared<Sprite>(100, 150);
		add(test);
	};
	PlayScene::~PlayScene() = default;

	void PlayScene::create() {
		Scene::create();
	}
}
