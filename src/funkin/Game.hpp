#pragma once

#include "Scene.hpp"

namespace funkin {
	class Game final {
		public:
			static void start(const Scene &initialScene);
			static void update(float delta);

			static Scene scene;
	};
}
