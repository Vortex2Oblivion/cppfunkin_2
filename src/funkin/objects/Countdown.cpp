#include "Countdown.hpp"

#include <array>
#include <format>

#include "funkin/sound/SoundManager.hpp"
#include "funkin/utilities/Timer.hpp"
#include "funkin/utilities/Tween.hpp"

namespace funkin::objects {
	Countdown::Countdown(const float beatLength, const float x, const float y) : Group(x, y) {
		this->beatLength = beatLength;

		std::string countdownPath = "assets/images/noteskins/funkin/countdown";

		readySprite = std::make_shared<Sprite>();
		readySprite->loadTexture(std::format("{}/ready.png", countdownPath));
		readySprite->screenCenter();
		readySprite->alpha = 0.0f;
		add(readySprite);

		setSprite = std::make_shared<Sprite>();
		setSprite->loadTexture(std::format("{}/set.png", countdownPath));
		setSprite->screenCenter();
		setSprite->alpha = 0.0f;
		add(setSprite);

		goSprite = std::make_shared<Sprite>();
		goSprite->loadTexture(std::format("{}/go.png", countdownPath));
		goSprite->screenCenter();
		goSprite->alpha = 0.0f;
		add(goSprite);
	}

	Countdown::~Countdown() = default;

	void Countdown::start() const {
		std::array<std::shared_ptr<Sprite>, 4> countdownSprites = {nullptr, std::ref(readySprite), std::ref(setSprite), std::ref(goSprite)};
		for (uint8_t i = 0; i < 4; i++) {
			std::array<std::string, 4> countdownSounds = {"THREE", "TWO", "ONE", "GO"};
			utilities::Timer::create(static_cast<float>(i) * beatLength, [countdownSprites, i, this, countdownSounds] {
				sound::SoundManager::playSound(std::format("assets/sounds/intro{}.ogg", countdownSounds[i]));
				if (countdownSprites[i] == nullptr) {
					return;
				}
				countdownSprites[i]->alpha = 1.0f;
				utilities::Tween::create({{&countdownSprites[i]->alpha, 0.0f}}, beatLength, EASE_IN_OUT_CUBIC, [i, this] {
					if (i == static_cast<uint8_t>(CountdownTick::GO)) {
						onFinish();
					}
					onTick(static_cast<CountdownTick>(i));
				})->start();
			})->start();
		}
	}
} // namespace funkin::objects
