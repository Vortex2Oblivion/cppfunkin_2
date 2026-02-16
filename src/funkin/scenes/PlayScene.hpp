#pragma once

#include "Scene.hpp"

namespace funkin::scenes {
	class PlayScene : public Scene {
		public:
			PlayScene();
			~PlayScene() override;
		protected:
			void create() override;
	};
}
