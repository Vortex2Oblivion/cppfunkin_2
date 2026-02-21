#include "PlayField.hpp"

namespace funkin::game {
	PlayField::PlayField(const float x, const float y, const std::uint8_t keyCount, const float speed, const std::vector<data::NoteData>& noteDatas, const std::shared_ptr<Conductor>& conductor) : Group(x, y) {
		for (std::uint8_t i = 0; i < keyCount; i++) {
			std::vector<data::NoteData> noteDatasToAdd = {};
			for (auto noteData : noteDatas) {
				if (noteData.lane == i) {
					noteDatasToAdd.push_back(noteData);
				}
			}
			const auto noteLane = std::make_shared<NoteLane>(i * 100, 0, noteDatasToAdd, conductor);
			noteLane->speed = speed;
			add(noteLane);
		}
	}

	PlayField::~PlayField() = default;
}
