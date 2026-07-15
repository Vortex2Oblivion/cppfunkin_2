#include "HealthBar.hpp"

namespace funkin::objects {
	HealthBar::HealthBar(const float x, const float y, Color colorLeft, Color colorRight, const std::string& iconLeft, const std::string& iconRight) : Group(x, y) {
		bar = std::make_shared<ui::Bar>(0, 0, 592, 12, colorLeft, colorRight, BLACK);
		bar->borderSize = 4.0f;
		bar->fillDirection = ui::FillDirection::RIGHT_TO_LEFT;
		add(bar);

		this->iconLeft = std::make_shared<Sprite>();
		this->iconLeft->loadTexture("assets/characters/"+iconLeft+"/icon.png");
		this->iconLeft->centerOn(bar, math::Axes::Y);
		add(this->iconLeft);

		this->iconRight = std::make_shared<Sprite>();
		this->iconRight->loadTexture("assets/characters/"+iconRight+"/icon.png");
		this->iconRight->centerOn(bar, math::Axes::Y);
		add(this->iconRight);
	}
	HealthBar::~HealthBar() = default;
} // namespace funkin::objects
