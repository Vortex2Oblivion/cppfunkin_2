#include "SoundManager.hpp"

#include <iostream>
#include <ranges>


namespace funkin::sound {
	float SoundManager::checkEvery = 1.0f;

	std::unordered_map<std::string, Sound> SoundManager::soundCache = {};
	std::vector<Sound> SoundManager::soundAliases = {};
	float SoundManager::soundCheckTime = 0.0f;

	void SoundManager::playSound(const std::string &path) {
		cacheSound(path);
		soundAliases.push_back(LoadSoundAlias(soundCache[path]));
		PlaySound(soundAliases.back());
	}
	void SoundManager::playSoundWithoutCaching(const std::string &path) {
		cacheSound(path);
		PlaySound(LoadSound(path.c_str()));
	}

	void SoundManager::cacheSound(const std::string &path) {
		if (!soundCache.contains(path)) {
			soundCache[path] = LoadSound(path.c_str());
		}
	}

	void SoundManager::clearCache() {
		soundCheckTime = 0.0f;
		for (const auto sound: soundAliases) {
			UnloadSoundAlias(sound);
		}
		soundAliases.clear();

		for (const auto &val: soundCache | std::views::values) {

			UnloadSound(val);
		}
		soundCache.clear();
	}

	void SoundManager::update(const float delta) {
#ifdef false
		soundCheckTime += delta;


		if (soundCheckTime < checkEvery) {
			return;
		}

		std::erase_if(soundAliases, [](const auto &soundAlias) {
			const bool isPlaying = IsSoundPlaying(soundAlias);
			if (!isPlaying) {
				UnloadSoundAlias(soundAlias);
			}
			return !isPlaying;
		});

		soundCheckTime = 0.0f;
#endif
	}
} // namespace funkin::sound
