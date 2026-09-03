#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"

namespace funkin::sound {
	class SoundManager {
	public:
		static float checkEvery;

		static void playSound(const std::string &path);
		static void playSoundWithoutCaching(const std::string &path);
		static void cacheSound(const std::string &path);

		static void clearCache();

		static void update(float delta);

	private:
		static float soundCheckTime;
		static std::unordered_map<std::string, Sound> soundCache;
		static std::vector<Sound> soundAliases;
	};
} // namespace funkin::sound
