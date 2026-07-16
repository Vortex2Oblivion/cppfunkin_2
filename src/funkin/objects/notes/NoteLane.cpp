#include "NoteLane.hpp"

#include <algorithm>
#include <iostream>

#include "StrumNote.hpp"
#include "funkin/game/Conductor.hpp"

namespace funkin::objects::notes {

	NoteLane::NoteLane(const float x, const float y, const std::vector<data::NoteData> &noteDatas, std::uint8_t lane,
					   const std::shared_ptr<game::Conductor> &conductor) : Group(x, y) {
		this->noteDatas = noteDatas;
		this->conductor = conductor;
		this->lane = lane;
		sustains = std::make_shared<Group<Note>>();
		add(sustains);
		strum = std::make_shared<StrumNote>(lane);
		add(strum);
		notes = std::make_shared<Group<Note>>();
		add(notes);
		std::ranges::sort(this->noteDatas, [](const data::NoteData a, const data::NoteData b) { return a.time < b.time; });
	}

	NoteLane::~NoteLane() {
		noteDatas.clear();
		toInvalidate.clear();
	};

	void NoteLane::update(const float delta) {
		Group::update(delta);
		while (!noteDatas.empty() && noteDataIndex < noteDatas.size() &&
			   ceilf(conductor->time) >= floorf(noteDatas[noteDataIndex].time - spawnTime)) {
			auto data = noteDatas[noteDataIndex];
			const auto note = std::make_shared<Note>(data.time, data.lane, speed);
			if (noteDatas[noteDataIndex].length > 0) {
				const auto sustain = std::make_shared<Note>(data.time, data.lane, speed, true, data.length);
				sustain->setupSustain(note, strum);
				sustains->add(sustain);
			}
			notes->add(note);
			noteDataIndex++;
		}

		float closestDistance = INFINITY;

		if (!botplay) {
			pressed = IsKeyPressed(bind);
			held = IsKeyDown(bind);
			if (pressed) {
				strum->animation.play("press", true);
				strum->centerOffsets();
			}
		}

		for (const auto &sustain: sustains->members) {
			const float hitWindow = conductor->time;
			if (hitWindow > sustain->strumTime + maxHitTime + sustain->sustainLength) {
				toInvalidate.push_back(sustain);
			}
			sustain->updateY(conductor->time, 0);

			const float _minHitTime = botplay ? 0 : minHitTime;

			float minHitWindow = hitWindow + _minHitTime;

			if (sustain->wasHit) {
				minHitWindow += sustain->sustainLength;
			}

			const float maxHitWindow = hitWindow - maxHitTime - sustain->sustainLength;
			const bool hittable = sustain->strumTime <= minHitWindow && sustain->strumTime >= maxHitWindow;

			if ((held || botplay) && hittable && sustain->parentNote->wasHit) {
				if (strum->getCurrentAnimation()->currentFrame >= 2 || strum->getCurrentAnimation()->name != "confirm") {
					strum->animation.play("confirm", true);
				}
				strum->centerOffsets();
				sustain->wasHit = true;
				const float addScore = holdScore * delta;
				score += addScore;
				health += addScore / 2.0f;
				lastHealth = addScore / 2.0f;
				health = Clamp(health, 0.0f, 100.0f);
				onNoteHit(sustain);
			}
		}

		for (const auto &note: notes->members) {
			const float hitWindow = conductor->time;

			if (hitWindow > note->strumTime + maxHitTime) {
				misses++;
				score -= missPenalty;
				onNoteMiss(note);
				toInvalidate.push_back(note);
			}

			note->updateY(conductor->time, 0);

			const float _minHitTime = botplay ? 0 : minHitTime;

			const float minHitWindow = (hitWindow + _minHitTime);
			const float maxHitWindow = (hitWindow - maxHitTime);

			const bool hittable = note->strumTime <= minHitWindow && note->strumTime >= maxHitWindow;

			if (!hittable) {
				continue;
			}

			const float distance = std::abs(note->strumTime - conductor->time);

			if (distance > closestDistance) {
				continue;
			}

			closestDistance = distance;

			if (pressed || botplay) {
				strum->animation.play("confirm", true);
				strum->centerOffsets();
				note->wasHit = true;
				const float addScore = std::min(maxScore, maxScore - abs(note->strumTime - conductor->time));
				score += addScore;
				const float addHealth = addScore / 250.0f;
				health += addHealth;
				health = Clamp(health, 0.0f, 100.0f);
				lastHealth = addHealth;
				onNoteHit(note);
				toInvalidate.push_back(note);
			}
		}

		if (botplay ? strum->animation.isFinished() : !held) {
			strum->animation.play("static", true);
			strum->centerOffsets();
		}

		for (const auto &note: toInvalidate) {
			if (note->sustainNote) {
				sustains->remove(note);
			} else {
				notes->remove(note);
			}
		}
		toInvalidate.clear();
	}
} // namespace funkin::objects::notes
