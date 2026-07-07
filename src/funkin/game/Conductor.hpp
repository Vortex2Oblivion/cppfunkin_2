#pragma once

#include <vector>

#include "eventpp/callbacklist.h"
#include "raylib.h"

namespace funkin::game {
	class Conductor {
	public:
		explicit Conductor(const std::vector<Music> &tracks = {});

		~Conductor();

		std::vector<Music> tracks = {};

		bool playing = false;

		float time = 0.0f;
		float bpm = 60.0f;
		std::uint16_t beat = 0;
		std::uint16_t step = 0;

		float crochet = 60.0f / bpm;
		float stepCrochet = crochet / 4.0f;

		eventpp::CallbackList<void(std::uint16_t)> onBeatHit;
		eventpp::CallbackList<void(std::uint16_t)> onStepHit;

		void start();

		void stop();

		void pause();

		void resume();

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