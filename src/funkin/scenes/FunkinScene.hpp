#pragma once

#include "funkin/Scene.hpp"
#include "funkin/game/Conductor.hpp"

namespace funkin::scenes {
	class FunkinScene : public Scene {
	public:
		FunkinScene();
		~FunkinScene() override;

		void update(float delta) override;

		static std::shared_ptr<game::Conductor> conductor;
	};
} // namespace funkin::scenes
