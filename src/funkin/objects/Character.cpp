
#include "Character.hpp"

namespace funkin::objects {
	Character::Character(const float x, const float y, const std::string& characterName, const CharacterType type) : Sprite(x, y) {
		this->characterName = characterName;
		this->type = type;

		const std::string basePath = "assets/characters/" + characterName;

		loadTexture(basePath + "/spritesheet.png");
		if (FileExists((basePath + "/spritesheet.txt").c_str())) {
			animation.loadPacker(basePath + "/spritesheet.txt");
		}
		else {
			animation.loadSparrow(basePath + "/spritesheet.xml");
		}

		script = std::make_shared<modding::LuaScript>(basePath + "/character.lua");
		script->call("onCreateCharacter", this);
	}

	Character::~Character() = default;

	void Character::update(const float delta) {
		Sprite::update(delta);
		if (animation.currentAnimation->name.starts_with("sing")) {
			holdTimer += delta;
		}
	}
} // namespace funkin::objects
