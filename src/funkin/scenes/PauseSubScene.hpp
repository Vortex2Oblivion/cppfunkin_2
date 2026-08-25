#pragma once

#include "funkin/Scene.hpp"
#include "funkin/ui/AlphabetList.hpp"
#include "funkin/objects/Alphabet.hpp"
#include "funkin/utilities/CoolUtil.hpp"
#include "funkin/game/Conductor.hpp"
#include "raylib.h"

using Conductor = funkin::game::Conductor;

namespace funkin::scenes {
	class PauseSubScene : public Scene {
	public:
		explicit PauseSubScene(std::string _songName,std::string _difficulty);
		~PauseSubScene() override;

		std::string songName;
		std::string difficulty;
		bool pending_close = false;
		std::shared_ptr<AlphabetList> menuAlphabets = std::make_shared<AlphabetList>();

		std::array<std::string, 3> menuOptions = {"Resume", "Restart", "Main Menu"};

		void open();
		void close();
		void exit();
		void restart();

		void update(float delta) override;
	};
} // namespace funkin::scenes
