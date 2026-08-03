#pragma once

#include "Scene.hpp"
#include "Sprite.hpp"
#include "objects/debug/PerformanceTracker.hpp"

namespace funkin {
	class Game final {
	public:
		static void start(std::unique_ptr<Scene> initialScene);
		static void switchScene(std::unique_ptr<Scene> newScene);
		template<typename T = Object>
		static void add(const std::shared_ptr<T> &object) {
			scene->add(std::shared_ptr<Object>(object));
		}

		static void update(float delta);

		static void shutdown();

		static bool isSwitching();

		static std::unique_ptr<Scene> scene;
		static std::vector<std::shared_ptr<Camera>> cameras;
		static std::shared_ptr<Camera> defaultCamera;

		static objects::debug::PerformanceTracker performanceTracker;
	private:

		static void _switchScene(std::unique_ptr<Scene> newScene);

		static bool switching;
		static std::unique_ptr<Scene> nextScene;
	};
} // namespace funkin
