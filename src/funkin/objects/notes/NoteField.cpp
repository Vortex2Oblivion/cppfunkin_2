#include "NoteField.hpp"

#include "rlgl.h"

namespace funkin::objects::notes {
	NoteField::NoteField(const float x, const float y, const uint8_t keyCount, const float speed,
						 const std::vector<data::NoteData> &noteDatas, const std::shared_ptr<game::Conductor> &conductor) : Group(x, y) {

		constexpr std::array binds = {KEY_D, KEY_F, KEY_J, KEY_K};

		for (uint8_t i = 0; i < keyCount; i++) {
			std::vector<data::NoteData> noteDatasToAdd = {};

			for (auto noteData: noteDatas) {
				if (noteData.lane == i) {
					noteDatasToAdd.push_back(noteData);
				}
			}

			const auto noteLane = std::make_shared<NoteLane>(i * 160 * 0.7, 0, noteDatasToAdd, i, conductor, this);
			noteLane->speed = speed;
			noteLane->bind = binds[i];
			add(noteLane);
		}

		origin = Vector2{.x = static_cast<float>(keyCount) * members[0]->position.x,
						 .y = (static_cast<float>(GetRenderHeight()) - y) / 2.0f};
	}

	NoteField::~NoteField() = default;

	void NoteField::calculateAccuracy() {
		if (interactedNotes != 0) {
			accuracy = 100.0f / (static_cast<float>(interactedNotes) / notesHit);
		}
	}

	uint16_t NoteField::getMisses() const {
		uint16_t misses = 0;
		for (const auto &lane: members) {
			misses += lane->misses;
		}
		return misses;
	}

	int NoteField::getScore() const {
		float score = 0;
		for (const auto &lane: members) {
			score += lane->score;
		}
		return floor(score);
	}

	bool NoteField::getBotplay() const { return botplay; }

	void NoteField::setBotplay(const bool value) {
		botplay = value;
		for (const auto &lane: members) {
			lane->botplay = value;
		}
	}
} // namespace funkin::objects::notes
