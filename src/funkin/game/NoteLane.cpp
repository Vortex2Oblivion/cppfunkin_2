#include "NoteLane.hpp"

#include <iostream>

namespace funkin::game {
	NoteLane::NoteLane(const float x, const float y, const std::vector<data::NoteData>& noteDatas, const std::shared_ptr<Conductor>& conductor) : Group(x, y) {
		this->noteDatas = noteDatas;
		this->conductor = conductor;
		strum = std::make_shared<StrumNote>();
		strum->loadTexture("assets/images/slungus.png");
		add(strum);
		notes = std::make_shared<Group<Note>>();
		add(notes);
	}

	NoteLane::~NoteLane() {
		noteDatas.clear();
	};

	void NoteLane::update(const float delta) {
		Group::update(delta);
		while (!noteDatas.empty() &&  noteDataIndex < noteDatas.size() && ceilf(conductor->time) >= floorf(noteDatas[noteDataIndex].time - spawnTime)) {
			auto data = noteDatas[noteDataIndex];
			const auto note = std::make_shared<Note>(data.time, data.lane, speed);
			/*if (data.length > 0) {
				const auto sustain = std::make_shared<Note>(data.time, data.lane, speed, true);
				const auto roundSustainLength = static_cast<size_t>(roundf(data.length / conductor->stepCrochet));
				const auto scale = roundSustainLength * Note::pixelsPerMS * speed;
				sustain->source = Rectangle{.x = static_cast<float>(data.lane) * 104.0f, .y = 0, .width = 52, .height = 300};
				notes->add(sustain);
			}*/
			notes->add(note);
			noteDataIndex++;
		}
		for (const auto& note : notes->members) {
			note->updateY(conductor->time, 0);
		}
	}
}
