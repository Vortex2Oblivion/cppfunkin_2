#include "Game.hpp"


namespace funkin {

	Group<>& Game::scene = _scene;
	Group<> Game::_scene;

	void Game::start(const Group<>& initialScene) {
		scene = initialScene;
	}
}
