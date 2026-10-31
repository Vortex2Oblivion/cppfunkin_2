#include "Tween.hpp"

#include <algorithm>

#include "raymath.h"

namespace funkin::utilities {

	std::vector<std::shared_ptr<Tween>> Tween::tweens = {};

	Tween::Tween(const std::unordered_map<float *, float> &values, const float duration, const std::function<float(float)> &ease,
				 const std::function<void()> &onComplete) : Timer(duration, onComplete), originalValues(values) {
		this->values = values;
		this->ease = ease;
	}

	Tween::~Tween() { onComplete(); }

	std::shared_ptr<Tween> Tween::create(const std::unordered_map<float *, float> &values, float duration,
										 const std::function<float(float)> &ease, const std::function<void()> &onComplete) {
		auto tween = std::make_shared<Tween>(values, duration, ease, onComplete);
		tweens.push_back(tween);
		return tween;
	}

	void Tween::update(const float delta) {
		Timer::update(delta);
		for (auto const &[key, val]: values) {
			*key = Lerp(originalValues[key], val, std::min(1.0f, ease(timer / duration)));
		}
	}

	std::function<float(float)> Tween::easeFromString(std::string ease) {
		std::ranges::transform(ease, ease.begin(), tolower);
		if (ease == "sinein") {
			return EASE_IN_SINE;
		}
		if (ease == "sineout") {
			return EASE_OUT_SINE;
		}
		if (ease == "sineinout") {
			return EASE_IN_OUT_SINE;
		}
		if (ease == "cubein") {
			return EASE_IN_CUBIC;
		}
		if (ease == "cubeout") {
			return EASE_OUT_CUBIC;
		}
		if (ease == "cubeinout") {
			return EASE_IN_OUT_CUBIC;
		}
		if (ease == "quintin") {
			return EASE_IN_QUINT;
		}
		if (ease == "quintout") {
			return EASE_OUT_QUINT;
		}
		if (ease == "quintinout") {
			return EASE_IN_OUT_QUINT;
		}
		if (ease == "circin") {
			return EASE_IN_CIRC;
		}
		if (ease == "circout") {
			return EASE_OUT_CIRC;
		}
		if (ease == "circinout") {
			return EASE_IN_OUT_CIRC;
		}
		if (ease == "quadin") {
			return EASE_IN_QUAD;
		}
		if (ease == "quadout") {
			return EASE_OUT_QUAD;
		}
		if (ease == "quadinout") {
			return EASE_IN_OUT_QUAD;
		}
		if (ease == "quartin") {
			return EASE_IN_QUART;
		}
		if (ease == "quartout") {
			return EASE_OUT_QUART;
		}
		if (ease == "quartinout") {
			return EASE_IN_OUT_QUART;
		}
		if (ease == "expoin") {
			return EASE_IN_EXPO;
		}
		if (ease == "expoout") {
			return EASE_OUT_EXPO;
		}
		if (ease == "expoinout") {
			return EASE_IN_OUT_EXPO;
		}
		if (ease == "backin") {
			return EASE_IN_BACK;
		}
		if (ease == "backout") {
			return EASE_OUT_BACK;
		}
		if (ease == "backinout") {
			return EASE_IN_OUT_BACK;
		}
		if (ease == "bouncein") {
			return EASE_IN_BOUNCE;
		}
		if (ease == "bounceout") {
			return EASE_OUT_BOUNCE;
		}
		if (ease == "bounceinout") {
			return EASE_IN_OUT_BOUNCE;
		}
		if (ease == "elasticin") {
			return EASE_IN_ELASTIC;
		}
		if (ease == "elasticout") {
			return EASE_OUT_ELASTIC;
		}
		if (ease == "elasticinout") {
			return EASE_IN_OUT_ELASTIC;
		}
		if (ease == "smoothstepin") {
			return EASE_IN_SMOOTH_STEP;
		}
		if (ease == "smoothstepout") {
			return EASE_OUT_SMOOTH_STEP;
		}
		if (ease == "smoothstepinout") {
			return EASE_IN_OUT_SMOOTH_STEP;
		}
		if (ease == "smootherstepin") {
			return EASE_IN_SMOOTHER_STEP;
		}
		if (ease == "smootherstepout") {
			return EASE_OUT_SMOOTHER_STEP;
		}
		if (ease == "smootherstepinout") {
			return EASE_IN_OUT_SMOOTHER_STEP;
		}
		return EASE_LINEAR;
	}

} // namespace funkin::utilities
