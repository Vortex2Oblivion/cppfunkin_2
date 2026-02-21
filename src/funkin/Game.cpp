#include "Game.hpp"

namespace funkin {
	std::unique_ptr<Scene> Game::scene;

	void Game::start(std::unique_ptr<Scene> initialScene) {
		scene = std::move(initialScene);
		scene->create();
	}

	void Game::update(const float delta) {
		if (scene->initialized && scene->alive) {
			scene->update(delta);
			scene->draw(0, 0);
		}
	}
}