#include "Object.hpp"

namespace funkin {
	Object::Object(const float x, const float y) {
		position = Vector2(x, y);
		alive = true;
	}
	Object::~Object() {
		alive = false;
	}

	void Object::Update(float delta) {};

	void Object::Draw(float x, float y) {};
}
