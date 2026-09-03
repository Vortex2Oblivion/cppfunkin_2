#pragma once

#include <memory>
#include <string>

#include "funkin/Sprite.hpp"
#include "funkin/modding/LuaScript.hpp"

namespace funkin::objects {

	enum class CharacterType { BOYFRIEND, DAD, GIRLFRIEND };

	class Character : public Sprite {
	public:
		Character(float x, float y, const std::string &characterName, CharacterType type);
		~Character() override;

		bool dancesLeftAndRight = false;
		std::uint8_t danceEvery = 2;
		float holdTimer = 0.0f;
		float singDuration = 1.0f;
		CharacterType type = CharacterType::DAD;
		Color barColor = RED;
		Vector2 cameraOffset = Vector2Zero();

		std::string characterName;

		std::shared_ptr<modding::LuaScript> script = nullptr;

		bool canDance(float stepCrochet) const;
		void dance(bool force = false);

		void update(float delta) override;
	protected:
		bool danced = false;
	};

} // namespace funkin::objects
