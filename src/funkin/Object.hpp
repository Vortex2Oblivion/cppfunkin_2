#pragma once

#include "raylib.h"
#include "raymath.h"

namespace funkin {
	class Object {
	public:
		explicit Object(float x = 0.0f, float y = 0.0f);

		virtual ~Object();

		Vector2 position = Vector2Zero();
		bool alive = false;

		virtual void update(float delta);

		virtual void draw(float x, float y);
	};
}