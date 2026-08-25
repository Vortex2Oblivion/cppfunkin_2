#pragma once

#include "FunkinScene.hpp"
#include "funkin/objects/Alphabet.hpp"
#include "funkin/ui/AlphabetList.hpp"
#include "funkin/Text.hpp"
#include "funkin/utilities/CoolUtil.hpp"
#include "nlohmann/json.hpp"
#include "raylib.h"

namespace funkin::scenes {
	class FreeplayScene : public FunkinScene {
	public:
		FreeplayScene();
		~FreeplayScene() override;
		int curDifficulty = 0;
		std::vector<std::vector<std::string>> difficulties = {};
		std::shared_ptr<AlphabetList> songTexts = std::make_shared<AlphabetList>();


		std::shared_ptr<Sprite> menuBG = nullptr;
		std::shared_ptr<Text> difficultyText = nullptr;


		void changeDifficulty(int change);
		void changeSelection(int change);

		void update(float delta) override;
	protected:
		void create() override;
	};
} // namespace funkin::scenes
