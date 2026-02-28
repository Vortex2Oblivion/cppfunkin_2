#pragma once

#include "Conductor.hpp"
#include "Scene.hpp"
#include "LuaScript.hpp"

namespace funkin::scenes {
	using namespace game;

	class PlayScene : public Scene {
	public:
		PlayScene();

		~PlayScene() override;

		std::shared_ptr<Conductor> conductor;
		std::vector<std::shared_ptr<modding::LuaScript>> scripts = {};

		std::shared_ptr<Camera> camHUD;

		Music inst = {};
		Music voices = {};
		Music voicesPlayer = {};

	protected:
		void create() override;

		void update(float delta) override;
	};
}