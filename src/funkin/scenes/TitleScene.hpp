#pragma once

#include <array>

#include "FunkinScene.hpp"
#include "funkin/Sprite.hpp"
#include "funkin/group/SpriteGroup.hpp"
#include "funkin/objects/Alphabet.hpp"

namespace funkin::scenes {
	class TitleScene : public FunkinScene {
	public:
		TitleScene();
		~TitleScene() override;

		std::shared_ptr<Sprite> logoBumpin = nullptr;
		std::shared_ptr<Sprite> gfDance = nullptr;
		std::shared_ptr<Sprite> pressEnterText = nullptr;

		std::shared_ptr<group::SpriteGroup<objects::Alphabet>> textGroup = nullptr;
		std::shared_ptr<Sprite> newgroundsLogo = nullptr;

		static bool initialized;

		void addIntroText(const std::string &text) const;

		void skipIntro();

		void update(float delta) override;

	protected:
		bool skippedIntro = false;
		bool finishedFadeIn = false;

		std::array<Color, 2> titleColors = {Color{.r = 51, .g = 255, .b = 255, .a = 255}, Color{.r = 51, .g = 51, .b = 204, .a = 255}};
		float colorTime = 0.0f;

		void create() override;
	};
} // namespace funkin::scenes
