#include "PerformanceTracker.hpp"


#include <cmath>
#include <format>

#include "funkin/Game.hpp"
#include "funkin/modding/PlutoScript.hpp"
#include "funkin/utilities/CoolUtil.hpp"
#include "funkin/utilities/ProcessInfo.hpp"

namespace funkin::objects::debug {
	PerformanceTracker::PerformanceTracker(const float x, const float y) : Text(x, y, "") {
		borderSize = 1.0f;
		size = 18.0f;
	}

	PerformanceTracker::~PerformanceTracker() = default;

	void PerformanceTracker::update(const float delta) {
		framesPassed++;
		const float deltaTime = std::fmaxf(delta, 0.0f);
		updateClock += deltaTime;

		if (updateClock >= 1.0f) {
			fps = framesPassed;
			formattedDRAM = utilities::CoolUtil::formatBytes(utilities::ProcessInfo::getMemoryUsage(), 2);
			formattedVRAM = utilities::CoolUtil::formatBytes(getEstimatedVRAMUsage(), 2);
			formattedLuaGC = utilities::CoolUtil::formatBytes(modding::PlutoScript::getTotalMemoryUsage(), 2);
			updateClock = 0.0f;
			framesPassed = 0;
		}
		text = std::format("{} FPS\nDRAM: {}\nVRAM: {}\nPluto GC: {}", fps, formattedDRAM, formattedVRAM, formattedLuaGC);
	}
} // namespace funkin::objects::debug
