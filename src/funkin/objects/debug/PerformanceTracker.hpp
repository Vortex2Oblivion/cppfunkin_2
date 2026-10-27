
#pragma once

#include <string>

#include "funkin/Text.hpp"

namespace funkin::objects::debug {
	class PerformanceTracker : public Text {
	public:
		PerformanceTracker(float x, float y);
		~PerformanceTracker() override;

		void update(float delta) override;

		uint16_t fps = 0;
		std::string formattedDRAM;
		std::string formattedVRAM;
		std::string formattedLuaGC;
		double CPU = 0;

	protected:
		float updateClock = INFINITY;
		uint16_t framesPassed = 0;
	};
} // namespace funkin::objects::debug
