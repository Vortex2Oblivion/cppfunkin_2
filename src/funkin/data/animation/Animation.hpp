#pragma once

#include <cstdint>
#include <vector>
#include "Frame.hpp"

namespace funkin::data::animation {
	class Animation {
		friend class AnimationController;
		public:
			explicit Animation(const std::vector<Frame> &frames, float framerate = 24.0f, bool looped = false);
			~Animation();

			std::vector<Frame> frames = {};
			float framerate = 24.0f;
			bool looped = false;

			std::uint8_t currentFrame = 0;

			void update(float delta);

			float frameTimer = 0.0f;
			float animationTimer = 0.0f;
			void resetFrame();
	};
}
