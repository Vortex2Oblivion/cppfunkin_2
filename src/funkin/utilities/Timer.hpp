#pragma once

#include <functional>
#include <memory>

namespace funkin::utilities {
	class Timer {
	public:
		Timer(float duration, const std::function<void()> &onComplete);
		virtual ~Timer();
		static std::shared_ptr<Timer> create(float duration, const std::function<void()> &onComplete);

		[[nodiscard]] bool isFinished() const;
		[[nodiscard]] bool isRunning() const;
		void start();
		virtual void update(float delta);

		static std::vector<std::shared_ptr<Timer>> timers;

	protected:
		bool running = false;
		bool finished = false;
		float duration = 0.0f;
		float updateTimer = 0.0f;
		std::function<void()> onComplete;
	};
} // namespace funkin::utilities
