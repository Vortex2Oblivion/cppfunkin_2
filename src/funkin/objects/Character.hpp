#pragma once

#include <memory>
#include <string>

#include "funkin/Sprite.hpp"


namespace funkin::modding {
	class LuaScript;
}
namespace funkin::objects {

	enum class CharacterType { BOYFRIEND, DAD, GIRLFRIEND };

	class Character : public Sprite {
	public:
		Character(float x, float y, const std::string &characterName, CharacterType type);
		~Character() override;

		bool dancesLeftAndRight = false;
		std::uint8_t danceEvery = 2;
		float holdTimer = 0.0f;
		float singDuration = 4.0f;
		CharacterType type = CharacterType::DAD;
		Color barColor = RED;

		std::string characterName;

		std::shared_ptr<modding::LuaScript> script = nullptr;

		bool canDance(float stepCrochet) const;
		void dance(bool force = false);

		void update(float delta) override;
	protected:
		bool danced = false;
	};

} // namespace funkin::objects
