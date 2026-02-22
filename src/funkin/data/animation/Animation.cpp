#include "Animation.hpp"

namespace funkin::data::animation {
	Animation::Animation(const std::vector<Frame> &frames, const float framerate, const bool looped) {
		this->frames = frames;
		this->framerate = framerate;
		this->looped = looped;
	}

	Animation::~Animation() {
		frames.clear();
	}

	void Animation::update(const float delta) {
		frameTimer += delta;
		animationTimer += delta;

		while (frameTimer >= 1.0f / framerate) {
			frameTimer -= 1.0f / framerate;
		if (currentFrame + 1 < frames.size()) {
				currentFrame++;
			}
		}

		if (looped && currentFrame + 1 >= frames.size()) {
			resetFrame();
		}
	}

	void Animation::resetFrame() {
		currentFrame = 0;
		frameTimer = 0.0f;
		animationTimer = 0.0f;
	}
}
