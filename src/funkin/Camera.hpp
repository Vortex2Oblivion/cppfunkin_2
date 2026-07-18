#pragma once
#include <memory>
#include <vector>


#include "graphics/Shader.hpp"
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

		Color backgroundColor = BLANK;
		Color color = WHITE;

		std::vector<std::shared_ptr<graphics::Shader>> shaders = {};

		[[nodiscard]] Vector2 getScreenToWorld(Vector2 pos) const;
		[[nodiscard]] Vector2 getWorldToScreen(Vector2 pos) const;

		[[nodiscard]] Camera2D getCamera() const;
		[[nodiscard]] RenderTexture getCanvas() const;
		void update(float delta);
	private:
		Camera2D camera{};
		RenderTexture canvas{};
	};
} // namespace funkin
