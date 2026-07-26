
#pragma once
#include <cstdint>

#include <string>

#include "funkin/Object.hpp"

namespace funkin::objects::debug {
	class PerformanceTracker : public Object {
		public:
			PerformanceTracker(float x, float y);
			~PerformanceTracker() override;

			void update(float delta) override;
			void draw(float x, float y, const std::shared_ptr<Camera> &cam) override;

			int fps = 0;
			std::size_t rawMemory = 0;
			std::string formattedMemory;
		protected:
			float updateClock = INFINITY;
			float previousTime = 0.0f;
			std::uint16_t framesPassed = 0;
	};
} // namespace funkin::objects::debug
