#include "NoteLane.hpp"
#include "StrumNote.hpp"

namespace funkin::objects::notes {
	NoteLane::NoteLane(const float x, const float y, const std::vector<data::NoteData> &noteDatas, std::uint8_t lane, const std::shared_ptr<game::Conductor> &conductor) : Group(x, y) {
		this->noteDatas = noteDatas;
		this->conductor = conductor;
		this->lane = lane;
		strum = std::make_shared<StrumNote>(lane);
		add(strum);
		notes = std::make_shared<Group<Note>>();
		add(notes);
	}

	NoteLane::~NoteLane() {
		noteDatas.clear();
		toInvalidate.clear();
	};

	void NoteLane::update(const float delta) {
		Group::update(delta);
		while (!noteDatas.empty() && noteDataIndex < noteDatas.size() && ceilf(conductor->time) >= floorf(
			       noteDatas[noteDataIndex].time - spawnTime)) {
			auto data = noteDatas[noteDataIndex];
			const auto note = std::make_shared<Note>(data.time, data.lane, speed);
			if (noteDatas[noteDataIndex].length > 0) {
				const auto sustain = std::make_shared<Note>(data.time, data.lane, speed, true);
				const float scale = data.length / (conductor->stepCrochet * 1000) * Note::pixelsPerMS * speed;
				sustain->source = Rectangle{.x = static_cast<float>(data.lane) * 73, .y = 0, .width = 36, .height = 210};
				sustain->position.x += sustain->source.width * 2.0f;
				sustain->origin.x = sustain->source.width;
				sustain->origin.y = 0;
				sustain->scale.y = scale;
				notes->add(sustain);
			}
			notes->add(note);
			noteDataIndex++;
		}

		float closestDistance = INFINITY;

		if (!botplay) {
			pressed = IsKeyPressed(bind);
			held = IsKeyDown(bind);
			if (pressed) {
				strum->animation.play("press");
				strum->centerOffsets();
			}
		}

		for (const auto &note: notes->members) {
			const float hitWindow = conductor->time;

			if (hitWindow > note->strumTime + maxHitTime && !note->sustainNote) {
				toInvalidate.push_back(note);
			}
			note->updateY(conductor->time, 0);

			const float minHitWindow = (hitWindow + maxHitTime);
			const float maxHitWindow = (hitWindow - maxHitTime);

			const bool hittable = note->strumTime <= minHitWindow && note->strumTime >= maxHitWindow;

			if (!hittable) {
				continue;
			}

			const float distance = note->strumTime - conductor->time;

			if (distance > closestDistance) {
				continue;
			}
			closestDistance = distance;

			if (pressed) {
				strum->animation.play("confirm");
				strum->centerOffsets();
				if (!note->sustainNote) {
					toInvalidate.push_back(note);
				}
			}

		}

		if (!pressed && !held) {
			strum->animation.play("static");
			strum->centerOffsets();
		}

		for (const auto& note : toInvalidate) {
			notes->remove(note);
		}
		toInvalidate.clear();
	}
}
