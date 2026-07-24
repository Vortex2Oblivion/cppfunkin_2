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
		Vector2 scale = Vector2One();

		void setText(const std::string& newText);

	protected:
		std::string text;
	};

} // namespace funkin::objects
