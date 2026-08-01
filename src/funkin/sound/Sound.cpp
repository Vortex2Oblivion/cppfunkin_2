#include "Sound.hpp"

namespace funkin::sound {
	Sound::Sound(const std::string &path, const bool streamed) {
		this->streamed = streamed;
		if (streamed) {
			LoadMusicStream(path.c_str());
		} else {
			LoadSound(path.c_str());
		}
	}

	Sound::~Sound() {
		UnloadMusicStream(music);
		UnloadSound(sound);
	}

	bool Sound::getStreamed() const { return streamed; }

	bool Sound::isValid() const { return streamed ? IsMusicValid(music) : IsSoundValid(sound); }

	bool Sound::isPlaying() const { return streamed ? IsMusicStreamPlaying(music) : IsSoundPlaying(sound); }

	float Sound::getTime() const { return getTimeSeconds() * 1000.0f; }

	float Sound::getTimeSeconds() const { return GetMusicTimePlayed(music); }

	void Sound::setTime(const float milliseconds) const { setTimeSeconds(milliseconds / 1000.0f); }

	void Sound::setTimeSeconds(const float seconds) const {
		if (streamed) {
			SeekMusicStream(music, seconds);
		}
	}

	void Sound::play(const bool force) const {
		if (!force && isPlaying()) {
			return;
		}

		if (streamed) {
			PlayMusicStream(music);
		} else {
			PlaySound(sound);
		}
	}

	void Sound::stop() const {
		if (streamed) {
			StopMusicStream(music);
		} else {
			StopSound(sound);
		}
	}

	void Sound::pause() const {
		if (streamed) {
			PauseMusicStream(music);
		} else {
			PauseSound(sound);
		}
	}

	void Sound::resume() const {
		if (streamed) {
			ResumeMusicStream(music);
		} else {
			ResumeSound(sound);
		}
	}


	void Sound::update(float delta) const {
		if (streamed) {
			UpdateMusicStream(music);
		}
	}
} // namespace funkin::audio
// funkin
