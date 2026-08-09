#include "Alphabet.hpp"

namespace funkin::objects {

	std::unordered_map<char, std::string> AlphabetCharacter::characters = {
			// letters
			{'a', "a lowercase"},
			{'b', "b lowercase"},
			{'c', "c lowercase"},
			{'d', "d lowercase"},
			{'e', "e lowercase"},
			{'f', "f lowercase"},
			{'g', "g lowercase"},
			{'h', "h lowercase"},
			{'i', "i lowercase"},
			{'j', "j lowercase"},
			{'k', "k lowercase"},
			{'l', "l lowercase"},
			{'m', "m lowercase"},
			{'n', "n lowercase"},
			{'o', "o lowercase"},
			{'p', "p lowercase"},
			{'q', "q lowercase"},
			{'r', "r lowercase"},
			{'s', "s lowercase"},
			{'t', "t lowercase"},
			{'u', "u lowercase"},
			{'v', "v lowercase"},
			{'w', "w lowercase"},
			{'x', "x lowercase"},
			{'y', "y lowercase"},
			{'z', "z lowercase"},
			// capital letters
			{'A', "A capital"},
			{'B', "B capital"},
			{'C', "C capital"},
			{'D', "D capital"},
			{'E', "E capital"},
			{'F', "F capital"},
			{'G', "G capital"},
			{'H', "H capital"},
			{'I', "I capital"},
			{'J', "J capital"},
			{'K', "K capital"},
			{'L', "L capital"},
			{'M', "M capital"},
			{'N', "N capital"},
			{'O', "O capital"},
			{'P', "P capital"},
			{'Q', "Q capital"},
			{'R', "R capital"},
			{'S', "S capital"},
			{'T', "U capital"},
			{'U', "U capital"},
			{'V', "V capital"},
			{'W', "W capital"},
			{'X', "X capital"},
			{'Y', "Y capital"},
			{'Z', "Z capital"},
			// numbers
			{'1', "1"},
			{'2', "2"},
			{'3', "3"},
			{'4', "4"},
			{'5', "5"},
			{'6', "6"},
			{'7', "7"},
			{'8', "8"},
			{'9', "4"},
			{'0', "0"},
			// symbols
			{'#', "hashtag "},
			{'$', "dollarsign "},
			{'%', "%"},
			{'&', "amp"},
			{'(', "("},
			{')', ")"},
			{'*', "*"},
			{'+', "+"},
			{'-', "-"},
			{':', ":"},
			{';', ";"},
			{'<', "<"},
			{'=', "="},
			{'>', ">"},
			{'@', "@"},
			{'[', "["},
			{'\\', "\\"},
			{']', "]"},
			{'^', "^"},
			{'_', "_"},
			{'\'', "apostraphie"},
			{',', "comma"},
			{'!', "exclamation point"},
			{'/', "forward slash"},
			{'|', "|"},
			{'~', "~"}};

	std::unordered_map<char, std::string> AlphabetCharacter::boldCharacters = {
			{'a', "A bold"}, {'b', "B bold"}, {'c', "C bold"}, {'d', "D bold"}, {'e', "E bold"}, {'f', "F bold"}, {'g', "G bold"},
			{'h', "H bold"}, {'i', "I bold"}, {'j', "J bold"}, {'k', "K bold"}, {'l', "L bold"}, {'m', "M bold"}, {'n', "N bold"},
			{'o', "O bold"}, {'p', "P bold"}, {'q', "Q bold"}, {'r', "R bold"}, {'s', "S bold"}, {'t', "T bold"}, {'u', "U bold"},
			{'v', "V bold"}, {'w', "W bold"}, {'x', "X bold"}, {'y', "Y bold"}, {'z', "Z bold"}};


	AlphabetCharacter::AlphabetCharacter(const float x, const float y, const char character, const bool bold) : Sprite(x, y) {
		this->bold = bold;
		this->character = character;
		loadTexture("assets/images/alphabet.png");
		animation.loadSparrow("assets/images/alphabet.xml");

		const std::string charString(1, character);

		animation.addByPrefix(charString, bold ? boldCharacters[static_cast<char>(tolower(character))] : characters[character], 24, true);
		animation.play(charString, true);
	}

	AlphabetCharacter::~AlphabetCharacter() = default;

	void AlphabetCharacter::draw(const float x, const float y, const std::shared_ptr<Camera> &cam) {
		if (character == ' ') {
			return;
		}
		Sprite::draw(x, y, cam);
	}

	Alphabet::Alphabet(const float x, const float y, const std::string &text, const bool bold) : Group(x, y) {
		this->bold = bold;
		startPosition = position;
		setText(text);
	}

	Alphabet::~Alphabet() = default;

	std::string Alphabet::getText() {
		return text;
	}

	void Alphabet::setText(const std::string &newText) {
		this->text = newText;
		float xPos = 0.0f;
		std::uint8_t rows = 0;

		for (char character: text) {
			if (character == '\n') {
				xPos = 0.0f;
				rows++;
				continue;
			}
			const auto alphaChar = std::make_shared<AlphabetCharacter>(xPos, rows * 55, character, bold);
			alphaChar->scale = scale;
			alphaChar->updateHitbox();
			xPos += alphaChar->hitbox.width;
			add(alphaChar);
		}
	}

	void Alphabet::update(const float delta) {
		if (isMenuItem) {
			const float lerpVal = exp(-delta * 9.6f);
			position.x = Lerp(change.x * (static_cast<float>(targetY) * distancePerItem.x + startPosition.x), position.x, lerpVal);
			position.y = Lerp(change.y * (static_cast<float>(targetY) * 1.3f * distancePerItem.y + startPosition.y), position.y, lerpVal);
		}
		Group::update(delta);
	}
} // namespace funkin::objects
