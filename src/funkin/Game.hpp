#pragma once

#include "Scene.hpp"

namespace funkin {
	class Game final {
	public:
		static void start(std::unique_ptr<Scene> initialScene);

		static void update(float delta);

		static std::unique_ptr<Scene> scene;
	};
}