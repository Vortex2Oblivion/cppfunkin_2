#pragma once

#include <functional>
#include <memory>
#include <string>

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
#define EASE_IN_SINE [](float x) { return 1.0f - cos((x * PI) / 2.0f); }
#define EASE_OUT_SINE [](float x) { return sin((x * PI) / 2.0f); }
#define EASE_IN_OUT_SINE [](float x) { return -(cos(PI * x) - 1.0f) / 2.0f; }
#define EASE_IN_CUBIC [](float x) { return x * x * x; }
#define EASE_OUT_CUBIC [](float x) { return 1.0f - pow(1.0f - x, 3.0f); }
#define EASE_IN_OUT_CUBIC [](float x) { return x < 0.5f ? 4 * x * x * x : 1.0f - pow(-2.0f * x + 2.0f, 3) / 2.0f; }
#define EASE_IN_QUINT [](float x) { return x * x * x * x * x; }
#define EASE_OUT_QUINT [](float x) { return 1.0f - pow(1.0f - x, 5.0f); }
#define EASE_IN_OUT_QUINT [](float x) { return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - pow(-2.0f * x + 2.0f, 5) / 2.0f; }
#define EASE_IN_CIRC [](float x) { return 1.0f - sqrt(1.0f - pow(x, 2.0f)); }
#define EASE_OUT_CIRC [](float x) { return sqrt(1.0f - pow(x - 1.0f, 2.0f)); }
#define EASE_IN_OUT_CIRC                                                                                                                   \
	[](float x) {                                                                                                                          \
		return x < 0.5f ? (1.0f - sqrt(1.0f - pow(2.0f * x, 2.0f))) / 2.0f : (sqrt(1.0f - pow(-2.0f * x + 2.0f, 2.0f)) + 1) / 2.0f;        \
	}
#define EASE_IN_QUAD [](float x) { return x * x; }
#define EASE_OUT_QUAD [](float x) { return 1.0f - (1.0f - x) * (1.0f - x); }
#define EASE_IN_OUT_QUAD [](float x) { return x < 0.5f ? 2.0f * x * x : 1.0f - pow(-2.0f * x + 2.0f, 2.0f) / 2.0f; }
#define EASE_IN_QUART [](float x) { return x * x * x * x; }
#define EASE_OUT_QUART [](float x) { return 1.0f - pow(1.0f - x, 4); }
#define EASE_IN_OUT_QUART [](float x) { return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - pow(-2.0f * x + 2.0f, 4.0f) / 2.0f; }
#define EASE_IN_EXPO [](float x) { return x == 0.0f ? 0.0f : pow(2.0f, 10.0f * x - 10.0f); }
#define EASE_OUT_EXPO [](float x) { return x == 1.0f ? 1.0f : 1.0f - pow(2.0f, -10.0f * x); }
#define EASE_IN_OUT_EXPO                                                                                                                   \
	[](float x) {                                                                                                                          \
		return x == 0 ? 0 : x == 1.0f ? 1.0f : x < 0.5f ? pow(2.0f, 20 * x - 10) / 2.0f : (2.0f - pow(2.0f, -20 * x + 10)) / 2.0f;         \
	}
#define EASE_IN_BACK                                                                                                                       \
	[](float x) {                                                                                                                          \
		const float c1 = 1.70158;                                                                                                          \
		const float c3 = c1 + 1.0f;                                                                                                        \
		return c3 * x * x * x - c1 * x * x;                                                                                                \
	}
#define EASE_OUT_BACK                                                                                                                      \
	[](float x) {                                                                                                                          \
		const float c1 = 1.70158;                                                                                                          \
		const float c3 = c1 + 1.0f;                                                                                                        \
		return 1.0f + c3 * pow(x - 1.0f, 3) + c1 * pow(x - 1.0f, 2.0f);                                                                    \
	}
#define EASE_IN_OUT_BACK                                                                                                                   \
	[](float x) {                                                                                                                          \
		const float c1 = 1.70158;                                                                                                          \
		const float c2 = c1 * 1.525;                                                                                                       \
		return x < 0.5f ? (pow(2.0f * x, 2.0f) * ((c2 + 1) * 2.0f * x - c2)) / 2.0f                                                        \
						: (pow(2.0f * x - 2.0f, 2.0f) * ((c2 + 1) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;                                \
	}
#define EASE_OUT_BOUNCE [](float x) { return easeOutBounceHelper(x); }
#define EASE_IN_BOUNCE [](float x) { return 1.0f - easeOutBounceHelper(1.0f - x); }
#define EASE_IN_OUT_BOUNCE                                                                                                                 \
	[](float x) {                                                                                                                          \
		return x < 0.5f ? (1.0f - easeOutBounceHelper(1.0f - 2.0f * x)) / 2.0f : (1.0f + easeOutBounceHelper(2.0f * x - 1)) / 2.0f;        \
	}

// https://github.com/HaxeFlixel/flixel/blob/master/flixel/tweens/FlxEase.hx
#define ELASTIC_AMPLITUDE 1.0
#define ELASTIC_PERIOD 0.4

#define EASE_IN_ELASTIC                                                                                                                    \
	[](float x) {                                                                                                                          \
		return -(ELASTIC_AMPLITUDE * pow(2.0f, 10.0f * (x -= 1.0f)) *                                                                      \
				 sin((x - (ELASTIC_PERIOD / (2.0f * PI) * asin(1.0f / ELASTIC_AMPLITUDE))) * (2.0f * PI) / ELASTIC_PERIOD));               \
	}
#define EASE_OUT_ELASTIC                                                                                                                   \
	[](float x) {                                                                                                                          \
		return (ELASTIC_AMPLITUDE * pow(2.0f, -10 * x) *                                                                                   \
						sin((x - (ELASTIC_PERIOD / (2.0f * PI) * asin(1.0f / ELASTIC_AMPLITUDE))) * (2.0f * PI) / ELASTIC_PERIOD) +        \
				1.0f);                                                                                                                     \
	}
#define EASE_IN_OUT_ELASTIC                                                                                                                \
	[](float x) {                                                                                                                          \
		if (x < 0.5f) {                                                                                                                    \
			return -0.5f * (pow(2.0f, 10.0f * (x -= 0.5f)) * sin((x - (ELASTIC_PERIOD / 4.0f)) * (2.0f * PI) / ELASTIC_PERIOD));           \
		}                                                                                                                                  \
		return pow(2.0f, -10.0f * (x -= 0.5f)) * sin((x - (ELASTIC_PERIOD / 4.0f)) * (2.0f * PI) / ELASTIC_PERIOD) * 0.5f + 1.0f;          \
	}
#define EASE_IN_OUT_SMOOTH_STEP [](float x) { return x * x * (x * -2.0f + 3.0f); }
#define EASE_IN_SMOOTH_STEP [](float x) { return 2.0f * EASE_IN_OUT_SMOOTH_STEP(x / 2.0f); }
#define EASE_OUT_SMOOTH_STEP [](float x) { return 2.0f * EASE_IN_OUT_SMOOTH_STEP(x / 2.0f + 0.5f) - 1.0f; }
#define EASE_IN_OUT_SMOOTHER_STEP [](float x) { return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f); }
#define EASE_IN_SMOOTHER_STEP [](float x) { return 2.0f * EASE_IN_OUT_SMOOTHER_STEP(x / 2.0f); }
#define EASE_OUT_SMOOTHER_STEP [](float x) { return 2.0f * EASE_IN_OUT_SMOOTHER_STEP(x / 2.0f + 0.5f) - 1.0f; }


namespace funkin::utilities {
	class Tween : public Timer {
	public:
		Tween(
				const std::unordered_map<float *, float> &values, float duration, const std::function<float(float)> &ease = EASE_LINEAR,
				const std::function<void()> &onComplete = [] {});

		~Tween() override;
		static std::shared_ptr<Tween> create(
				const std::unordered_map<float *, float> &values, float duration, const std::function<float(float)> &ease = EASE_LINEAR,
				const std::function<void()> &onComplete = [] {});
		static std::vector<std::shared_ptr<Tween>> tweens;

		void update(float delta) override;

		static std::function<float(float)> easeFromString(std::string ease);

	private:
		std::unordered_map<float *, float> values = {};
		std::unordered_map<float *, float> originalValues;
		std::function<float(float)> ease = EASE_LINEAR;
	};
} // namespace funkin::utilities
