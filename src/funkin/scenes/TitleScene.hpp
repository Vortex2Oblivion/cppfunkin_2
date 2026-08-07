#pragma once

#include "FunkinScene.hpp"
#include "funkin/Sprite.hpp"
#include "funkin/objects/Alphabet.hpp"

namespace funkin::scenes {
	class TitleScene : public FunkinScene {
	public:
		TitleScene();
		~TitleScene() override;

		std::shared_ptr<Sprite> logoBumpin = nullptr;
		std::shared_ptr<Sprite> gfDance = nullptr;

		std::shared_ptr<Group<objects::Alphabet>> textGroup = nullptr;
		std::shared_ptr<Sprite> newgroundsLogo = nullptr;

		void createCoolText(const std::vector<std::string>& textArray) const;
		void addMoreText(const std::string &text) const;

		void update(float delta) override;

	protected:
		bool danceLeft = true;
		void create() override;
	};
} // namespace funkin::scenes
