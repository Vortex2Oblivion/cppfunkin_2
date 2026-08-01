#pragma once

#include <string>
#include "raylib.h"

namespace funkin::sound {
	class Sound {
	public:
		explicit Sound(const std::string& path, bool streamed = false);
		~Sound();

		[[nodiscard]] bool getStreamed() const;
		[[nodiscard]] bool isValid() const;
		[[nodiscard]] bool isPlaying() const;
		[[nodiscard]] float getTime() const;
		[[nodiscard]] float getTimeSeconds() const;

		void setTime(float milliseconds) const;
		void setTimeSeconds(float seconds) const;

		void play(bool force = false) const;
		void stop() const;
		void pause() const;
		void resume() const;


		void update(float delta) const;

	protected:
		bool streamed = false;

		float time = 0.0f;

		::Sound sound{};
		Music music{};
	};
} // namespace funkin::audio
