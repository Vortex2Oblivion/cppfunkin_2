#include "PerformanceTracker.hpp"


#include <cmath>
#include <iostream>

#include "funkin/Game.hpp"
#include "funkin/utilities/CoolUtil.hpp"
#include "funkin/utilities/ProcessInfo.hpp"

namespace funkin::objects::debug {
	PerformanceTracker::PerformanceTracker(const float x, const float y) : Object(x, y) {}

	PerformanceTracker::~PerformanceTracker() = default;

	void PerformanceTracker::update(const float delta) {
		framesPassed++;
		const float deltaTime = std::fmaxf(static_cast<float>(GetTime()) - previousTime, 0.0f);
		updateClock += deltaTime;

		if (updateClock >= 1.0f) {
			fps = framesPassed;
			formattedDRAM = utilities::CoolUtil::formatBytes(utilities::ProcessInfo::getMemoryUsage(), 2);
			formattedVRAM = utilities::CoolUtil::formatBytes(Sprite::getEstimatedVRAMUsage(), 2);
			updateClock = 0.0f;
			framesPassed = 0;
		}

		previousTime = static_cast<float>(GetTime());
	}

	void PerformanceTracker::draw(const float x, const float y, const std::shared_ptr<Camera>&) {
		DrawText(TextFormat("%i FPS\nDRAM: %s\nVRAM: %s", fps, formattedDRAM.c_str(), formattedVRAM.c_str()), static_cast<int>(position.x + x), static_cast<int>(position.y + y),
				 18, GREEN);
	}

} // namespace funkin::objects::debug
