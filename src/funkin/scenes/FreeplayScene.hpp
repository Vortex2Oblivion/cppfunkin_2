#pragma once

#include "FunkinScene.hpp"
#include "funkin/objects/Alphabet.hpp"

namespace funkin::scenes {
	class FreeplayScene : public FunkinScene {
	public:
		FreeplayScene();
		~FreeplayScene() override;

		int curSelected = 0;

		std::shared_ptr<Sprite> menuBG = nullptr;
		std::shared_ptr<Group<objects::Alphabet>> songTexts = nullptr;

		Sound scrollMenu{};

		void changeSelection(int change);

		void update(float delta) override;
	protected:
		void create() override;
	};
} // namespace funkin::scenes
