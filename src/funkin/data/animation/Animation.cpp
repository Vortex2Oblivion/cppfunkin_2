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
	}
}
