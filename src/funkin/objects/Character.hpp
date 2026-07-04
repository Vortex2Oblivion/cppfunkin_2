
#pragma once
#include "LuaScript.hpp"
#include "Sprite.hpp"

namespace funkin::objects {

	enum CharacterType {
		BOYFRIEND,
		DAD,
		GIRLFRIEND
	};

	class Character : public Sprite {
		public:
			Character(float x, float y, const std::string& characterName, CharacterType type);
			~Character() override;

			CharacterType type;
			std::string characterName;
			float holdTimer = 0.0f;
			float singDuration = 4.0f;
			std::uint8_t danceEvery = 2;

			std::shared_ptr<modding::LuaScript> script = nullptr;

			void update(float delta) override;
	};

} // namespace funkin::objects
