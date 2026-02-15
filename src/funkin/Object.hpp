#pragma once

#include "raylib.h"
#include "raymath.h"

namespace funkin {
	class Object {
		public:
			explicit Object(float x = 0.0f, float y = 0.0f);
			~Object();

			Vector2 position = Vector2Zero();
			bool alive = false;

			void Update(float delta);
			void Draw(float x, float y);
	};
}
