#pragma once

#include <array>


#include "funkin/Scene.hpp"
#include "funkin/game/Conductor.hpp"
#include "funkin/objects/Alphabet.hpp"
#include "funkin/ui/AlphabetList.hpp"
#include "funkin/utilities/CoolUtil.hpp"
#include "raylib.h"

using Conductor = funkin::game::Conductor;

namespace funkin::scenes {
	class PauseSubScene : public Scene {
	public:
		explicit PauseSubScene(const std::string &_songName, const std::string &_difficulty);
		~PauseSubScene() override;

		std::string songName;
		std::string difficulty;
		bool pending_close = false;
		std::shared_ptr<AlphabetList> menuAlphabets = std::make_shared<AlphabetList>();

		std::array<std::string, 3> menuOptions = {"Resume", "Restart", "Main Menu"};

		//void open();
		void close();
		static void exit();
		void restart();

		void update(float delta) override;
		void draw(float x, float y, const std::shared_ptr<Camera> &cam) override;
	};
} // namespace funkin::scenes
