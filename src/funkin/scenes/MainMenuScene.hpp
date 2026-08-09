#pragma once

#include <array>

#include "FunkinScene.hpp"
#include "funkin/Sprite.hpp"

namespace funkin::scenes {
	class MainMenuScene : public FunkinScene {
	public:
		MainMenuScene();
		~MainMenuScene() override;

		std::shared_ptr<Sprite> menuBG = nullptr;
		std::shared_ptr<Group<Sprite>> menuButtons = nullptr;

		std::array<std::string, 3> menuItems = {"storymode", "freeplay", "options"};

		void changeSelection(std::int8_t change);
		void update(float delta) override;

	protected:
		void create() override;
		std::uint8_t curSelected = 0;
	};
} // namespace funkin::scenes
