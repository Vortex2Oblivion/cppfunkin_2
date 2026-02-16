#include "Conductor.hpp"

#include <iostream>
#include <ostream>

namespace funkin::game {
	Conductor::Conductor(const std::vector<Music>& tracks) {
		this->tracks = tracks;
	}

	Conductor::~Conductor() {
		stop();
		tracks.clear();
	}

	void Conductor::start() const {
		if (tracks.empty()) {
			return;
		}
		for (const auto track : tracks) {
			PlayMusicStream(track);
		}
	}

	void Conductor::stop() const {
		if (tracks.empty()) {
			return;
		}
		for (const auto track : tracks) {
			StopMusicStream(track);
		}
	}

	void Conductor::pause() const {
		if (tracks.empty()) {
			return;
		}
		for (const auto track : tracks) {
			PauseMusicStream(track);
		}
	}

	void Conductor::resume() const {
		if (tracks.empty()) {
			return;
		}
		for (const auto track : tracks) {
			ResumeMusicStream(track);
		}
	}

	void Conductor::update(const float delta) {
		if (tracks.empty()) {
			return;
		}

		for (const auto track : tracks) {
			UpdateMusicStream(track);
		}

		const auto track = tracks.front();

		if (const float _time = GetMusicTimePlayed(track); lastMixPos != _time) {
			lastMixPos = _time;
			lastMixTimer = 0.0f;
		}
		else {
			lastMixTimer += delta;
		}
		time = lastMixPos + lastMixTimer;

		crochet = 60.0f / bpm;
		stepCrochet = crochet / 4.0f;

		const int oldStep = step;
		const int oldBeat = beat;

		updateStep();
		updateBeat();

		if (oldStep != step) {
			stepHit();
		}

		if (oldBeat != beat) {
			beatHit();
		}
	}

	void Conductor::updateStep() {
		const int potentialNewStep = static_cast<int>(time / stepCrochet);
		if (potentialNewStep != step) {
			step = potentialNewStep;
		}
	}

	void Conductor::updateBeat() {
		const int potentialNewBeat = static_cast<int>(time / crochet);
		if (potentialNewBeat != beat) {
			beat = potentialNewBeat;
		}
	}

	void Conductor::stepHit() const {
		//std::cout << "step hit:" << step << std::endl;
	}

	void Conductor::beatHit() const {
		std::cout << "beat hit:" << beat << std::endl;
	}
}
