#include "Camera.hpp"

#include "raymath.h"

namespace funkin {
	Camera::Camera() {
		camera = Camera2D{
			.offset = Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f},
			.target = Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f},
			.rotation = 0.0f,
			.zoom = 1.0f
		};
	}

	Camera::~Camera() = default;

	void Camera::begin() {
		camera.target = Vector2Add(target, Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f});
		camera.offset = Vector2Add(position, Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f});
		camera.zoom = zoom;
		camera.rotation = angle;
		BeginMode2D(camera);
	}
} // funkin