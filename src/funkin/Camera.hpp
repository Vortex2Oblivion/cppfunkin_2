#pragma once
#include "raylib.h"
#include "raymath.h"

namespace funkin {
	class Camera {

		friend class Sprite;

	public:
		Camera();
		~Camera();

		float angle = 0.0f;
		float zoom = 1.0f;

		Vector2 target = Vector2Zero();
		Vector2 position = Vector2Zero();

		Vector2 follow = Vector2Zero();

		void begin();
		[[nodiscard]] Vector2 getScreenToWorld(Vector2 pos) const;
		[[nodiscard]] Vector2 getWorldToScreen(Vector2 pos) const;

	private:
		Camera2D camera{};
	};
} // namespace funkin
