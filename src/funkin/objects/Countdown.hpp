#pragma once

#include "eventpp/callbacklist.h"
#include "funkin/Group.hpp"

namespace funkin::objects {
	enum class CountdownTick : uint8_t {
		THREE,
		TWO,
		ONE,
		GO
	};
	class Countdown : public Group<> {
	public:
		explicit Countdown(float beatLength, float x = 0.0f, float y = 0.0f);
		~Countdown() override;

		eventpp::CallbackList<void()> onFinish;
		eventpp::CallbackList<void(CountdownTick)> onTick;

		void start() const;

	protected:
		float beatLength;
		std::shared_ptr<Sprite> readySprite = nullptr;
		std::shared_ptr<Sprite> setSprite = nullptr;
		std::shared_ptr<Sprite> goSprite = nullptr;
	};
} // namespace funkin::objects
