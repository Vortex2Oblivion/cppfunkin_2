#include "PlayField.hpp"

namespace funkin::game {
	PlayField::PlayField(const float x, const float y, const std::uint8_t keyCount, const float speed, const std::vector<data::NoteData>& noteDatas, const std::shared_ptr<Conductor>& conductor) : Group(x, y) {
		for (std::uint8_t i = 0; i < 4; i++) {
			const auto noteLane = std::make_shared<NoteLane>(i * 42, 0, noteDatas, conductor);
			noteLane->speed = speed;
			add(noteLane);
		}
	}

	PlayField::~PlayField() = default;
}
