#include "CoolUtil.hpp"

#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>

#include "Ease.hpp"
#include "raylib.h"
#include "raytween.h"

namespace funkin::utilities {
	std::string CoolUtil::formatBytes(std::size_t bytes, const std::uint8_t precision) {
		const std::array<std::string, 5> suffix = {"B", "KB", "MB", "GB", "TB"};

		int i = 0;
		auto dblBytes = static_cast<double>(bytes);

		if (bytes > 1024) {
			for (i = 0; (bytes / 1024) > 0 && i < suffix.size() - 1; i++, bytes /= 1024) {
				dblBytes = static_cast<double>(bytes) / 1024.0;
			}
		}
		return TextFormat("%.*lf %s", precision, dblBytes, suffix[i].c_str());
	}

	std::function<float(float)> CoolUtil::easeFromString(std::string ease) {
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

	std::string CoolUtil::trim(std::string str) {
		str.erase(str.find_last_not_of(' ') + 1); // Suffixing spaces
		str.erase(0, str.find_first_not_of(' ')); // Prefixing spaces
		return str;
	}

	std::vector<std::string> CoolUtil::split(std::string str, const std::string& delimiter) {
		std::vector<std::string> tokens;
		size_t pos = 0;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			std::string token = str.substr(0, pos);
			tokens.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		tokens.push_back(str);

		return tokens;
	}
} // namespace funkin::utilities
