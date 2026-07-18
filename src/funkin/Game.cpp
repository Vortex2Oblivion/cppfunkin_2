#include "Game.hpp"

#include "Sprite.hpp"
#include "Text.hpp"
#include "raytween.h"

namespace funkin {
	std::unique_ptr<Scene> Game::scene;
	std::shared_ptr<Camera> Game::defaultCamera = nullptr;
	std::vector<std::shared_ptr<Camera>> Game::cameras = {};
	objects::debug::PerformanceTracker Game::performanceTracker = objects::debug::PerformanceTracker(10, 10);

	void Game::start(std::unique_ptr<Scene> initialScene) {
		scene = std::move(initialScene);
		defaultCamera = std::make_shared<Camera>();
		cameras = {defaultCamera};
		scene->create();
	}

	void Game::switchScene(std::unique_ptr<Scene> newScene) {
		scene->alive = false;
		scene->initialized = false;

		Sprite::clearTextureCache();
		game::AnimationController::clearFramesDataCache();
		Text::clearFontCache();

		cameras.clear();
		defaultCamera = std::make_shared<Camera>();
		cameras = {defaultCamera};

		scene = std::move(newScene);
		scene->create();
	}

	void Game::update(const float delta) {
		if (!scene->initialized || !scene->alive) {
			return;
		}

		BeginDrawing();
		ClearBackground(scene->backgroundColor);
		Raytween::DoTweens(delta);
		scene->update(delta);

		for (const auto &camera: cameras) {
			if (camera == nullptr) {
				continue;
			}
			camera->update(delta);

			BeginTextureMode(camera->getCanvas());
			ClearBackground(camera->backgroundColor);
			BeginMode2D(camera->getCamera());

			for (const auto &member: scene->members) {
				if (!member->alive || member->camera != camera) {
					continue;
				}
				member->draw(0.0f, 0.0f, camera);
			}

			EndMode2D();
			EndTextureMode();

			// https://www.reddit.com/r/raylib/comments/131ptxa/comment/ji2uyw2/
			BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);
			DrawTextureRec(camera->getCanvas().texture,
						   Rectangle{.x = 0,
									 .y = 0,
									 .width = static_cast<float>(camera->getCanvas().texture.width),
									 .height = static_cast<float>(-camera->getCanvas().texture.height)},
						   Vector2Zero(), camera->color);
			EndBlendMode();
		}

		performanceTracker.update(GetFrameTime());
		performanceTracker.draw(0, 0, nullptr);

		EndDrawing();
	}

} // namespace funkin
