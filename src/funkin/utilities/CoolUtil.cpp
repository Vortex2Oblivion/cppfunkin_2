#include "CoolUtil.hpp"

#include <array>
#include <cstring>
#include <iostream>
#include <random>

#include "raylib.h"

namespace funkin::utilities {
	std::string CoolUtil::formatBytes(const size_t bytes, const uint8_t precision) {
		const std::array<std::string, 5> suffix = {"B", "KB", "MB", "GB", "TB"};

		int i = 0;
		auto dblBytes = static_cast<double>(bytes);

		while (dblBytes > 1024 && i < suffix.size() - 1) {
			dblBytes /= 1024;
			i++;
		}

		return TextFormat("%.*lf %s", precision, dblBytes, suffix[i].c_str());
	}


	std::string CoolUtil::trim(std::string str) {
		str.erase(str.find_last_not_of(' ') + 1); // Suffixing spaces
		str.erase(0, str.find_first_not_of(' ')); // Prefixing spaces
		return str;
	}

	std::vector<std::string> CoolUtil::split(std::string str, const std::string &delimiter) {
		std::vector<std::string> tokens = {};
		if (delimiter.empty()) {
			for (const auto c: str) {
				const std::string charString(1, c);
				tokens.push_back(charString);
			}
		} else {
			size_t pos = 0;
			while ((pos = str.find(delimiter)) != std::string::npos) {
				std::string token = str.substr(0, pos);
				tokens.push_back(token);
				str.erase(0, pos + delimiter.length());
			}
			tokens.push_back(str);
		}

		return tokens;
	}

	bool CoolUtil::randomBool(const float chance) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::bernoulli_distribution d(chance / 100);
		return d(gen);
	}


	float CoolUtil::computeVelocity(float velocity, const float acceleration, const float drag, const float max, const float delta) {
		if (acceleration != 0) {
			velocity += acceleration * delta;
		} else if (drag != 0) {
			const float _drag = drag * delta;
			if (velocity - _drag > 0) {
				velocity -= _drag;
			} else if (velocity + _drag < 0) {
				velocity += _drag;
			} else {
				velocity = 0;
			}
		}
		if (velocity != 0 && max != 0) {
			if (velocity > max) {
				velocity = max;
			} else if (velocity < -max) {
				velocity = -max;
			}
		}
		return velocity;
	}
} // namespace funkin::utilities
