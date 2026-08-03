#include "HealthBar.hpp"

#include <iostream>

namespace funkin::objects {
	HealthBar::HealthBar(const float x, const float y, Color colorLeft, Color colorRight, const std::string &iconLeft,
						 const std::string &iconRight) : Group(x, y) {
		bar = std::make_shared<ui::Bar>(0, 0, 592, 12, colorLeft, colorRight, BLACK);
		bar->borderSize = 4.0f;
		bar->fillDirection = ui::FillDirection::RIGHT_TO_LEFT;
		add(bar);

		this->iconLeft = std::make_shared<Sprite>();
		this->iconLeft->loadTexture("assets/characters/" + iconLeft + "/icon.png");
		this->iconLeft->animation.addByRects("default", {Rectangle{.x = 0.0f, .y = 0.0f, .width = 150.0f, .height = 150.0f}});
		this->iconLeft->animation.addByRects("lose", {Rectangle{.x = 150.0f, .y = 0.0f, .width = 150.0f, .height = 150.0f}});
		this->iconLeft->animation.play("default");
		this->iconLeft->centerOn(bar, math::Axes::Y);
		this->iconLeft->updateHitbox();
		this->iconLeft->origin = Vector2{.x = this->iconLeft->hitbox.width, .y = 0.0f};
		add(this->iconLeft);

		this->iconRight = std::make_shared<Sprite>();
		this->iconRight->loadTexture("assets/characters/" + iconRight + "/icon.png");
		this->iconRight->animation.addByRects("default", {Rectangle{.x = 0.0f, .y = 0.0f, .width = 150.0f, .height = 150.0f}});
		this->iconRight->animation.addByRects("lose", {Rectangle{.x = 150.0f, .y = 0.0f, .width = 150.0f, .height = 150.0f}});
		this->iconRight->animation.play("default");
		this->iconRight->centerOn(bar, math::Axes::Y);
		this->iconRight->flipX = true;
		this->iconRight->updateHitbox();
		this->iconRight->origin = Vector2Zero();
		add(this->iconRight);
	}

	HealthBar::~HealthBar() = default;

	void HealthBar::bumpIcons() const {
		iconRight->scale = Vector2Scale(iconRight->scale, iconScale);
		iconLeft->scale = Vector2Scale(iconLeft->scale, iconScale);
	}

	void HealthBar::update(const float delta) {
		Group::update(delta);

		iconRight->position.x = bar->getMiddle() - iconOffset;
		iconLeft->position.x = bar->getMiddle() - iconLeft->hitbox.width + iconOffset;

		const float amount = expf(-delta * 9.0f);

		const float iconRightScale = Lerp(1.0f, iconRight->scale.x, amount);
		iconRight->scale.x = iconRightScale;
		iconRight->scale.y = iconRightScale;

		const float iconLeftScale = Lerp(1.0f, iconLeft->scale.x, amount);
		iconLeft->scale.x = iconLeftScale;
		iconLeft->scale.y = iconLeftScale;

		if (bar->progress >= 80) {
			iconLeft->animation.play("lose");
			iconRight->animation.play("default");
		} else if (bar->progress <= 20) {
			iconLeft->animation.play("default");
			iconRight->animation.play("lose");
		} else {
			iconLeft->animation.play("default");
			iconRight->animation.play("default");
		}
	}
} // namespace funkin::objects
