#pragma once

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
		std::shared_ptr<objects::Alphabet> pressEnterText = nullptr;

		std::shared_ptr<group::SpriteGroup<objects::Alphabet>> textGroup = nullptr;
		std::shared_ptr<Sprite> newgroundsLogo = nullptr;

		static bool initialized;

		void addIntroText(const std::string &text) const;

		void skipIntro();

		void update(float delta) override;
	protected:
		bool danceLeft = true;
		bool skippedIntro = false;
		void create() override;
	};
} // namespace funkin::scenes
