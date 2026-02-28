#include "Object.hpp"

#include "Game.hpp"

namespace funkin {
	Object::Object(const float x, const float y) {
		position = Vector2{.x = x, .y = y};
		camera = Game::defaultCamera;
		alive = true;
	}

	Object::~Object() {
		alive = false;
	}

	void Object::update(float delta) {
	};

	void Object::draw(float x, float y) {
	};
}