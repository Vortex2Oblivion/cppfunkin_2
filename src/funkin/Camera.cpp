#include "Camera.hpp"

#include "raymath.h"

namespace funkin {
	Camera::Camera() {
		camera = Camera2D{
				.offset = Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f},
				.target = Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f},
				.rotation = 0.0f,
				.zoom = 1.0f};
		canvas = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
	}

	Camera::~Camera() {
		if (!WindowShouldClose()) {
			UnloadRenderTexture(canvas);
		}
	};

	Vector2 Camera::getScreenToWorld(const Vector2 pos) const { return GetScreenToWorld2D(pos, camera); }

	Vector2 Camera::getWorldToScreen(const Vector2 pos) const { return GetWorldToScreen2D(pos, camera); }

	Camera2D Camera::getCamera() const { return camera; }

	RenderTexture Camera::getCanvas() const { return canvas; }

	bool Camera::containsPoint(const float x, const float y, const float width, const float height) const {
		return x + camera.offset.x + width > 0.0f && x < static_cast<float>(canvas.texture.width) &&
			   y + camera.offset.y + height > 0.0f && y < static_cast<float>(canvas.texture.height);
	}

	void Camera::update(const float delta) {
		if (follow != Vector2Zero()) {
			target = Vector2Lerp(target, follow, 1.0f - powf(1.0f - 0.04f, delta * 60.0f));
		}
		camera.target = Vector2Add(
				target, Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f});
		camera.offset = Vector2Add(
				position, Vector2{.x = static_cast<float>(GetScreenWidth()) / 2.0f, .y = static_cast<float>(GetScreenHeight()) / 2.0f});
		camera.zoom = zoom;
		camera.rotation = angle;
	}

} // namespace funkin
