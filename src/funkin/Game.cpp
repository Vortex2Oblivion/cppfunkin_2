#include "Game.hpp"

namespace funkin {

	Scene& Game::scene = _scene;
	Scene Game::_scene;

	void Game::start(const Scene& initialScene) {
		scene = initialScene;
		scene.create();
	}

	void Game::update(const float delta) {
		if (scene.initialized && scene.alive) {
			scene.update(delta);
			scene.draw(0, 0);
		}
	}
}
