#include "Game.hpp"

#include "Sprite.hpp"

namespace funkin {
	std::unique_ptr<Scene> Game::scene;
	std::shared_ptr<Camera> Game::defaultCamera = std::make_shared<Camera>();;
	std::vector<std::shared_ptr<Camera>> Game::cameras = {defaultCamera};

	void Game::start(std::unique_ptr<Scene> initialScene) {
		scene = std::move(initialScene);
		scene->create();
	}

	void Game::update(const float delta) {
		if (!scene->initialized || !scene->alive) {
			return;
		}
		scene->update(delta);

		for (const auto& camera : cameras) {
			if (camera == nullptr) {
				continue;
			}
			camera->begin();
			for (const auto& member : scene->members) {
				if (!member->alive || member->camera != camera) {
					continue;
				}
				member->draw(0.0f, 0.0f);
			}
			EndMode2D();
		}

	}

	void Game::add(Sprite* object) {
		scene->add(std::shared_ptr<Sprite>(object));

	}
}
