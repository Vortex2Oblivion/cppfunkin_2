#include "HealthIcon.hpp"

namespace funkin::objects {
	HealthIcon::HealthIcon(const float x, const float y, const std::string &character) : Sprite(x, y) {
		const char *iconPath = TextFormat("assets/characters/%s/icon.png", character.c_str());

		if (FileExists(iconPath)) {
			loadTexture(iconPath);
		} else {
			loadTexture("assets/images/placeholder icon.png");
		}

		animation.addByRects("default", {Rectangle{.x = 0.0f, .y = 0.0f, .width = 150.0f, .height = 150.0f}});
		animation.addByRects("lose", {Rectangle{.x = 150.0f, .y = 0.0f, .width = 150.0f, .height = 150.0f}});
		animation.play("default");
		Sprite::updateHitbox();
	}

	HealthIcon::~HealthIcon() = default;
} // namespace funkin::objects
