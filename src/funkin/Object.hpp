#pragma once

#include "raylib.h"
#include "raymath.h"

namespace funkin {
	class Object {
	public:
		explicit Object(float x = 0.0f, float y = 0.0f);

		virtual ~Object();

		bool alive = false;
		Vector2 position = Vector2Zero();

		virtual void update(float delta);
		virtual void draw(float x, float y);
	};
}