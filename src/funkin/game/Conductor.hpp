#pragma once
#include <cstdint>
#include <vector>

#include "raylib.h"

namespace funkin::game {
	class Conductor {
	public:
		explicit Conductor(const std::vector<Music> &tracks = {});

		~Conductor();

		std::vector<Music> tracks = {};

		float time = 0.0f;
		float bpm = 60.0f;
		uint16_t step = 0;
		uint16_t beat = 0;

		float crochet = 60.0f / bpm;
		float stepCrochet = crochet / 4.0f;

		void start() const;

		void stop() const;

		void pause() const;

		void resume() const;

		void update(float delta);

	private:
		float lastMixPos = 0.0f;
		float lastMixTimer = 0.0f;

		void beatHit() const;

		void stepHit() const;

		void updateBeat();

		void updateStep();
	};
}