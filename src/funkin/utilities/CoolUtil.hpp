#pragma once

#include <cstdint>
#include <functional>
#include <string>


namespace funkin::utilities {
	class CoolUtil {
	public:
		/**
		 * @see https://gist.github.com/dgoguerra/7194777
		 */
		static std::string formatBytes(std::size_t bytes, std::uint8_t precision = 2);

		static std::function<float(float)> easeFromString(std::string ease);

		static std::string trim(std::string str);

		static std::vector<std::string> split(std::string str, const std::string &delimiter);

		static bool randomBool(float chance);

		/**
		 *
		 * @param velocity
		 * @param acceleration
		 * @param drag
		 * @param max
		 * @param delta
		 * @return
		 * @see https://github.com/HaxeFlixel/flixel/blob/5e147e81bb59a441f4afed72ab9a8299d8211216/flixel/math/FlxVelocity.hx#L232s
		 */
		static float computeVelocity(float velocity, float acceleration, float drag, float max, float delta);
	};

} // namespace funkin::utilities
