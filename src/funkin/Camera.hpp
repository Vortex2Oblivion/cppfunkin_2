#pragma once
#include <memory>
#include <vector>


#include "graphics/Shader.hpp"
#include "raylib.h"
#include "raymath.h"

namespace funkin {
	class Camera {
		friend class Sprite;
		friend class Game;

	public:
		Camera();
		~Camera();

		float angle = 0.0f;
		float zoom = 1.0f;
		float flashAlpha = 0.0f;
		float flashDuration = 0.0f;
		Color flashColor = BLANK;

		Vector2 target = Vector2Zero();
		Vector2 position = Vector2Zero();

		Vector2 follow = Vector2Zero();

		BlendMode blend = BLEND_ALPHA;

		Color backgroundColor = BLANK;
		Color color = WHITE;

		std::vector<std::shared_ptr<graphics::Shader>> shaders = {};

		void flash(Color col = WHITE, float duration = 1.0f);

		[[nodiscard]] bool containsPoint(float x, float y, float width, float height) const;

		[[nodiscard]] Vector2 getScreenToWorld(Vector2 pos) const;
		[[nodiscard]] Vector2 getWorldToScreen(Vector2 pos) const;

		[[nodiscard]] Camera2D getCamera() const;
		[[nodiscard]] RenderTexture getCanvas() const;

		void update(float delta);
	private:
		bool flashIn = false;
		Camera2D camera{};
		RenderTexture canvas{};
	};
} // namespace funkin
