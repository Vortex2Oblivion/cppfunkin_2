#pragma once
#include "raylib.h"
#include "raymath.h"

namespace funkin {
	class Camera {
		public:
			Camera();
			~Camera();

			float angle = 0.0f;
			float zoom = 1.0f;

			Vector2 target = Vector2Zero();
			Vector2 position = Vector2Zero();

			void begin();
	private:
			Camera2D camera{};
	};
} // funkin