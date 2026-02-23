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
			notes->add(note);
			noteDataIndex++;
		}

		float closestDistance = INFINITY;

		if (!botplay) {
			pressed = IsKeyPressed(bind);
			held = IsKeyDown(bind);
			if (pressed) {
				strum->animation.play("confirm");
				strum->centerOffsets();
			}
		}

		for (const auto &note: notes->members) {
			const float hitWindow = conductor->time;

			if (hitWindow > note->strumTime + maxHitTime) {
				toInvalidate.push_back(note);
			}
			note->updateY(conductor->time, 0);
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
