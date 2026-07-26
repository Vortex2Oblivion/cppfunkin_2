#pragma once

#include <memory>

#include "Camera.hpp"
#include "raylib.h"
#include "raymath.h"

namespace funkin {
	class Object {
	public:
		explicit Object(float x = 0.0f, float y = 0.0f);

		virtual ~Object();

		bool alive = false;
		std::size_t ID = 0;
		Vector2 position = Vector2Zero();
		std::shared_ptr<Camera> camera = nullptr;

		virtual void update(float delta);
		virtual void draw(float x, float y, const std::shared_ptr<Camera>& cam);
	};
}