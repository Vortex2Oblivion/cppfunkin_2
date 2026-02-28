#pragma once

#include "Scene.hpp"
#include "Sprite.hpp"

namespace funkin {
	class Game final {
	public:
		static void start(std::unique_ptr<Scene> initialScene);
		static void add(Sprite* object);

		static void update(float delta);

		static std::unique_ptr<Scene> scene;
		static std::vector<std::shared_ptr<Camera>> cameras;
		static std::shared_ptr<Camera> defaultCamera;
	};
}
