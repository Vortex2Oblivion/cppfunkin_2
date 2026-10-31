#pragma once

#include <functional>
#include <memory>

#include "Timer.hpp"

static float easeOutBounceHelper(float x) {
	constexpr float n1 = 7.5625f;
	constexpr float d1 = 2.75f;

	if (x < 1.0f / d1) {
		return n1 * x * x;
	}
	if (x < 2.0f / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	return n1 * (x -= 2.625f / d1) * x + 0.984375f;
}

// https://github.com/SebasKoria/raytween/blob/main/raylib%20tweening%20engine/raytween.h
#define EASE_LINEAR [](float x) { return x; }
#define EASE_IN_SINE [](float x) { return 1 - cos((x * PI) / 2); }
#define EASE_OUT_SINE [](float x) { return sin((x * PI) / 2); }
#define EASE_IN_OUT_SINE [](float x) { return -(cos(PI * x) - 1) / 2; }
#define EASE_IN_CUBIC [](float x) { return x * x * x; }
#define EASE_OUT_CUBIC [](float x) { return 1 - pow(1 - x, 3); }
#define EASE_IN_OUT_CUBIC [](float x) { return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; }
#define EASE_IN_QUINT [](float x) { return x * x * x * x * x; }
#define EASE_OUT_QUINT [](float x) { return 1 - pow(1 - x, 5); }
#define EASE_IN_OUT_QUINT [](float x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2; }
#define EASE_IN_CIRC [](float x) { return 1 - sqrt(1 - pow(x, 2)); }
#define EASE_OUT_CIRC [](float x) { return sqrt(1 - pow(x - 1, 2)); }
#define EASE_IN_OUT_CIRC [](float x) { return x < 0.5 ? (1 - sqrt(1 - pow(2 * x, 2))) / 2 : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2; }
#define EASE_IN_QUAD [](float x) { return x * x; }
#define EASE_OUT_QUAD [](float x) { return 1 - (1 - x) * (1 - x); }
#define EASE_IN_OUT_QUAD [](float x) { return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2; }
#define EASE_IN_QUART [](float x) { return x * x * x * x; }
#define EASE_OUT_QUART [](float x) { return 1 - pow(1 - x, 4); }
#define EASE_IN_OUT_QUART [](float x) { return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2; }
#define EASE_IN_EXPO [](float x) { return x == 0 ? 0 : pow(2, 10 * x - 10); }
#define EASE_OUT_EXPO [](float x) { return x == 1 ? 1 : 1 - pow(2, -10 * x); }
#define EASE_IN_OUT_EXPO                                                                                                                   \
	[](float x) { return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? pow(2, 20 * x - 10) / 2 : (2 - pow(2, -20 * x + 10)) / 2; }
#define EASE_IN_BACK                                                                                                                       \
	[](float x) {                                                                                                                          \
		const float c1 = 1.70158;                                                                                                          \
		const float c3 = c1 + 1;                                                                                                           \
		return c3 * x * x * x - c1 * x * x;                                                                                                \
	}
#define EASE_OUT_BACK                                                                                                                      \
	[](float x) {                                                                                                                          \
		const float c1 = 1.70158;                                                                                                          \
		const float c3 = c1 + 1;                                                                                                           \
		return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);                                                                                \
	}
#define EASE_IN_OUT_BACK                                                                                                                   \
	[](float x) {                                                                                                                          \
		const float c1 = 1.70158;                                                                                                          \
		const float c2 = c1 * 1.525;                                                                                                       \
		return x < 0.5 ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2 : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;      \
	}
#define EASE_OUT_BOUNCE [](float x) { return easeOutBounceHelper(x); }
#define EASE_IN_BOUNCE [](float x) { return 1 - easeOutBounceHelper(1 - x); }
#define EASE_IN_OUT_BOUNCE                                                                                                                 \
	[](float x) { return x < 0.5 ? (1 - easeOutBounceHelper(1 - 2 * x)) / 2 : (1 + easeOutBounceHelper(2 * x - 1)) / 2; }

// https://github.com/HaxeFlixel/flixel/blob/master/flixel/tweens/FlxEase.hx
#define ELASTIC_AMPLITUDE 1.0
#define ELASTIC_PERIOD 0.4

#define EASE_IN_ELASTIC                                                                                                                    \
	[](float x) {                                                                                                                          \
		return -(ELASTIC_AMPLITUDE * pow(2, 10 * (x -= 1)) *                                                                               \
				 sin((x - (ELASTIC_PERIOD / (2 * PI) * asin(1 / ELASTIC_AMPLITUDE))) * (2 * PI) / ELASTIC_PERIOD));                        \
	}
#define EASE_OUT_ELASTIC                                                                                                                   \
	[](float x) {                                                                                                                          \
		return (ELASTIC_AMPLITUDE * pow(2, -10 * x) *                                                                                      \
						sin((x - (ELASTIC_PERIOD / (2 * PI) * asin(1 / ELASTIC_AMPLITUDE))) * (2 * PI) / ELASTIC_PERIOD) +                 \
				1);                                                                                                                        \
	}
#define EASE_IN_OUT_ELASTIC                                                                                                                \
	[](float x) {                                                                                                                          \
		if (x < 0.5) {                                                                                                                     \
			return -0.5 * (pow(2, 10 * (x -= 0.5)) * sin((x - (ELASTIC_PERIOD / 4)) * (2 * PI) / ELASTIC_PERIOD));                         \
		}                                                                                                                                  \
		return pow(2, -10 * (x -= 0.5)) * sin((x - (ELASTIC_PERIOD / 4)) * (2 * PI) / ELASTIC_PERIOD) * 0.5 + 1;                           \
	}
#define EASE_IN_OUT_SMOOTH_STEP [](float x) { return x * x * (x * -2 + 3); }
#define EASE_IN_SMOOTH_STEP [](float x) { return 2 * EASE_IN_OUT_SMOOTH_STEP(x / 2); }
#define EASE_OUT_SMOOTH_STEP [](float x) { return 2 * EASE_IN_OUT_SMOOTH_STEP(x / 2 + 0.5) - 1; }
#define EASE_IN_OUT_SMOOTHER_STEP [](float x) { return x * x * x * (x * (x * 6 - 15) + 10); }
#define EASE_IN_SMOOTHER_STEP [](float x) { return 2 * EASE_IN_OUT_SMOOTHER_STEP(x / 2); }
#define EASE_OUT_SMOOTHER_STEP [](float x) { return 2 * EASE_IN_OUT_SMOOTHER_STEP(x / 2 + 0.5) - 1; }


namespace funkin::utilities {
	class Tween : public Timer {
	public:
		Tween(
				const std::unordered_map<float *, float> &values, float duration, const std::function<float(float)> &ease = EASE_LINEAR,
				const std::function<void()> &onComplete = [] {});

		~Tween();
		static std::shared_ptr<Tween> create(
				const std::unordered_map<float *, float> &values, float duration, const std::function<float(float)> &ease = EASE_LINEAR,
				const std::function<void()> &onComplete = [] {});
		static std::vector<std::shared_ptr<Tween>> tweens;

		void update(float delta);

		static std::function<float(float)> easeFromString(std::string ease);

	private:
		float duration = 0.0f;
		float timer = 0.0f;
		std::unordered_map<float *, float> values = {};
		std::unordered_map<float *, float> originalValues;
		std::function<float(float)> ease = EASE_LINEAR;
	};
} // namespace funkin::utilities
