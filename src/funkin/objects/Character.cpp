#include "Character.hpp"

#include "funkin/modding/LuaScript.hpp"

namespace funkin::objects {
	Character::Character(const float x, const float y, const std::string &characterName, const CharacterType type) : Sprite(x, y) {
		this->characterName = characterName;
		this->type = type;
		std::string basePath = "assets/characters/" + characterName;
		if(!FileExists(basePath.c_str())){
			TraceLog(5,("Unable to load character '"+this->characterName+"'. Fallbacking to bf").c_str());
			this->characterName="bf";
			basePath = "assets/characters/bf";
		}

		loadTexture(basePath + "/spritesheet.png");
		if (FileExists((basePath + "/spritesheet.txt").c_str())) {
			animation.loadPacker(basePath + "/spritesheet.txt");
		} else {
			animation.loadSparrow(basePath + "/spritesheet.xml");
		}

		if (type == CharacterType::BOYFRIEND) {
			barColor = LIME;
			flipX = true;
		}

		script = std::make_shared<modding::LuaScript>(basePath + "/character.lua");
		script->call("onCreateCharacter", this);
	}

	Character::~Character() = default;

	bool Character::canDance(const float stepCrochet) const {
		const auto animationName = getCurrentAnimation()->name;
		return (holdTimer == 0.0f || 
				holdTimer > singDuration && animationName.starts_with("sing") && !animationName.ends_with("miss"));
	}

	void Character::dance(const bool force) {
		animation.play(dancesLeftAndRight ? ((danced=!danced) ? "danceLeft" : "danceRight") : "idle", force);
		
		holdTimer = 0.0f;
	}

	void Character::update(const float delta) {
		Sprite::update(delta);
		if (getCurrentAnimation()->name.starts_with("sing")) {
			holdTimer += delta;
		}
	}
} // namespace funkin::objects
