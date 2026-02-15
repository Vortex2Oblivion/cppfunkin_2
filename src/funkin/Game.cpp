#include "Game.hpp"

funkin::Group<> funkin::Game::scene;

namespace funkin {
	void Game::Start(const Group<>& initialScene) {
		scene = initialScene;
	}
}
