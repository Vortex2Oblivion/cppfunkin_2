#pragma once

#include "Conductor.hpp"
#include "Scene.hpp"


namespace funkin::scenes {
	using namespace game;

	class PlayScene : public Scene {
	public:
		PlayScene();

		~PlayScene() override;

		std::shared_ptr<Conductor> conductor;
		Music inst = {};
		Music voices = {};
		Music voicesPlayer = {};

	protected:
		void create() override;

		void update(float delta) override;
	};
}