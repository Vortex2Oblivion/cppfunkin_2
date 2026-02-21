#include "Object.hpp"

#include <iostream>
#include <ostream>

namespace funkin {
	Object::Object(const float x, const float y) {
		position = Vector2(x, y);
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