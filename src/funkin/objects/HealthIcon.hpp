#pragma once

#include "funkin/Sprite.hpp"

namespace funkin::objects {
	class HealthIcon : public Sprite {
	public:
		HealthIcon(float x, float y, const std::string &character);
		~HealthIcon() override;
	};
} // namespace funkin::objects
