#pragma once

#include "funkin//Sprite.hpp"
#include "funkin/Group.hpp"

namespace funkin::objects {
	class AlphabetCharacter : public Sprite {
	public:
		AlphabetCharacter(float x, float y, char character, bool bold = true);
		~AlphabetCharacter() override;

		bool bold = true;

		static std::unordered_map<char, std::string> characters;
		static std::unordered_map<char, std::string> boldCharacters;
	};

	class Alphabet : public Group<AlphabetCharacter> {
	public:
		Alphabet(float x, float y, const std::string &text, bool bold = true);
		~Alphabet() override;

		bool bold = true;
		bool isMenuItem = false;

		int targetY = 0;

		Vector2 scale = Vector2One();
		Vector2 change = Vector2One();

		Vector2 distancePerItem = Vector2{.x = 20.0f, .y = 120.0f};
		Vector2 startPosition = Vector2Zero();

		std::string getText();
		void setText(const std::string &newText);

		void update(float delta) override;

	protected:
		std::string text;
	};

} // namespace funkin::objects
