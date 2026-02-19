#include "NoteLane.hpp"

#include <iostream>

namespace funkin::game {
	NoteLane::NoteLane(const float x, const float y, const std::vector<data::NoteData>& noteDatas, const std::shared_ptr<Conductor>& conductor) : Group(x, y) {
		this->noteDatas = noteDatas;
		this->conductor = conductor;
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
			note->loadTexture("assets/images/slungus.png");
			notes->add(note);
			noteDataIndex++;
		}
		for (const auto& note : notes->members) {
			note->updateY(conductor->time, 50);
		}
	}
}
