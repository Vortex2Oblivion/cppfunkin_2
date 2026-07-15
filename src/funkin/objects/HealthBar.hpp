#pragma once

#include "funkin/Group.hpp"
#include "funkin/ui/Bar.hpp"

namespace funkin::objects {
	class HealthBar : public Group<> {
	public:
		HealthBar(float x, float y, Color colorLeft, Color colorRight, const std::string& iconLeft, const std::string& iconRight);
		~HealthBar() override;


		float iconOffset = 26.0f;
		float iconScale = 1.125f;

		std::shared_ptr<ui::Bar> bar = nullptr;

		std::shared_ptr<Sprite> iconLeft = nullptr;
		std::shared_ptr<Sprite> iconRight = nullptr;

		void bumpIcons() const;

		void update(float delta) override;
	};
} // namespace funkin::objects
