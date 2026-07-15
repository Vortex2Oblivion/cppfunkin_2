#pragma once

#include "funkin/Group.hpp"
#include "funkin/ui/Bar.hpp"

namespace funkin::objects {
	class HealthBar : public Group<> {
	public:
		HealthBar(float x, float y, Color colorLeft, Color colorRight, const std::string& iconLeft, const std::string& iconRight);
		~HealthBar() override;

		std::shared_ptr<ui::Bar> bar = nullptr;

		std::shared_ptr<Sprite> iconLeft = nullptr;
		std::shared_ptr<Sprite> iconRight = nullptr;
	};
} // namespace funkin::objects
