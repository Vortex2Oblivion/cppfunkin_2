#include "PlayField.hpp"

#include "rlgl.h"

namespace funkin::objects::notes {
	PlayField::PlayField(const float x, const float y, const std::uint8_t keyCount, const float speed,
						 const std::vector<data::NoteData> &noteDatas, const std::shared_ptr<game::Conductor> &conductor) : Group(x, y) {

		constexpr std::array binds = {KEY_D, KEY_F, KEY_J, KEY_K};

		for (std::uint8_t i = 0; i < keyCount; i++) {
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

	PlayField::~PlayField() = default;

	void PlayField::calculateAccuracy() {
		accuracy = 100.0f / (static_cast<float>(interactedNotes) / notesHit);
	}

	std::uint16_t PlayField::getMisses() const {
		std::uint16_t misses = 0;
		for (const auto &lane: members) {
			misses += lane->misses;
		}
		return misses;
	}

	std::int32_t PlayField::getScore() const {
		float score = 0;
		for (const auto &lane: members) {
			score += lane->score;
		}
		return floor(score);
	}

	bool PlayField::getBotplay() const { return botplay; }

	void PlayField::setBotplay(const bool value) {
		botplay = value;
		for (const auto &lane: members) {
			lane->botplay = value;
		}
	}

	void PlayField::draw(const float x, const float y, const std::shared_ptr<Camera> &cam) {
		Matrix m = MatrixIdentity();

		m.m1 = tan(skew.x * DEG2RAD);
		m.m2 = tan(skew.y * DEG2RAD);

		rlPushMatrix();
		rlTranslatef(-origin.x - x, -origin.y - y, 0.0f);
		rlScalef(scale.x, scale.y, 1.0f);
		rlMultMatrixf(&m.m0);
		rlTranslatef(origin.x + x, origin.y + y, 0.0f);

		Group::draw(x, y, cam);

		rlPopMatrix();
	}
} // namespace funkin::objects::notes
