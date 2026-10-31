#include "Timer.hpp"

namespace funkin::utilities {

	std::vector<std::shared_ptr<Timer>> Timer::timers = {};

	Timer::Timer(const float duration, const std::function<void()> &onComplete) {
		this->duration = duration;
		this->onComplete = onComplete;
	}

	Timer::~Timer() {
		onComplete();
	}

	void Timer::start() {
		running = true;
	}

	bool Timer::isRunning() const {
		return running;
	}

	bool Timer::isFinished() const {
		return finished;
	}

	void Timer::update(const float delta) {
		updateTimer += delta;
		if (updateTimer >= duration) {
			finished = true;
			running = false;
		}
	}

	std::shared_ptr<Timer> Timer::create(float duration, const std::function<void()> &onComplete) {
		auto timer = std::make_shared<Timer>(duration, onComplete);
		timers.push_back(timer);
		return timer;
	}
} // namespace funkin::utilities
