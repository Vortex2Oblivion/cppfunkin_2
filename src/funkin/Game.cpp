#include "Game.hpp"

#include <cfloat>

#include "Sprite.hpp"
#include "Text.hpp"
#include "raytween.h"
#include "sound/SoundManager.hpp"

namespace funkin {
	std::unique_ptr<Scene> Game::scene;
	std::shared_ptr<Camera> Game::defaultCamera = nullptr;
	std::vector<std::shared_ptr<Camera>> Game::cameras = {};
	objects::debug::PerformanceTracker Game::performanceTracker = objects::debug::PerformanceTracker(10, 10);

	std::unique_ptr<Scene> Game::nextScene = nullptr;
	bool Game::switching = false;

	void Game::start(std::unique_ptr<Scene> initialScene) {
		scene = std::move(initialScene);
		defaultCamera = std::make_shared<Camera>();
		cameras = {defaultCamera};
		scene->create();
	}

	void Game::switchScene(std::unique_ptr<Scene> newScene) {
		nextScene = std::move(newScene);
		switching = true;
	}

	void Game::_switchScene(std::unique_ptr<Scene> newScene) {
		scene->alive = false;
		scene->initialized = false;

		// cancel all tweens
		Raytween::DoTweens(FLT_MAX);

		Sprite::clearTextureCache();
		game::AnimationController::clearFramesDataCache();
		Text::clearFontCache();
		sound::SoundManager::clearCache();

		cameras.clear();
		defaultCamera = std::make_shared<Camera>();
		cameras = {defaultCamera};

		scene = std::move(newScene);
		scene->create();

		defaultCamera->flash(BLACK, 0.5f);
		switching = false;
		nextScene = nullptr;
	}

	void Game::shutdown() {
		nextScene.reset();
		scene.reset();
		cameras.clear();
		defaultCamera.reset();
		switching = false;

		Sprite::clearTextureCache();
		game::AnimationController::clearFramesDataCache();
		Text::clearFontCache();
		sound::SoundManager::clearCache();
	}

	bool Game::isSwitching() { return switching; }

	void Game::update(const float delta) {
		if (!scene->initialized || !scene->alive || switching) {
			return;
		}

		BeginDrawing();
		ClearBackground(scene->backgroundColor);

		Raytween::DoTweens(delta);
		sound::SoundManager::update(delta);
		scene->update(delta);

		for (const auto &camera: cameras) {
			if (camera == nullptr) {
				continue;
			}

			camera->update(delta);

			if (!camera->shaders.empty()) {
				BeginTextureMode(camera->getCanvas());
				ClearBackground(camera->backgroundColor);
			} else if (camera->backgroundColor.a != 0) {
				DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), camera->backgroundColor);
			}
			BeginMode2D(camera->getCamera());

			for (const auto &member: scene->members) {
				if (!member->alive || member->camera != camera) {
					continue;
				}
				member->draw(0.0f, 0.0f, camera);
			}

			if (camera->flashAlpha > 0.0f) {
				DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), ColorAlpha(camera->flashColor, camera->flashAlpha));
			}

			EndMode2D();
			if (!camera->shaders.empty()) {
				EndTextureMode();

				BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);
				for (const auto &shader: camera->shaders) {
					BeginShaderMode(shader->getShader());
				}
				DrawTextureRec(camera->getCanvas().texture,
							   Rectangle{.x = 0,
										 .y = 0,
										 .width = static_cast<float>(camera->getCanvas().texture.width),
										 .height = static_cast<float>(-camera->getCanvas().texture.height)},
							   Vector2Zero(), camera->color);

				for (size_t i = 0; i < camera->shaders.size(); i++) {
					EndShaderMode();
				}
				EndBlendMode();
			}
		}

		performanceTracker.update(GetFrameTime());
		performanceTracker.draw(0, 0, nullptr);

		EndDrawing();

		if (nextScene != nullptr) {
			_switchScene(std::move(nextScene));
		}
	}

} // namespace funkin
