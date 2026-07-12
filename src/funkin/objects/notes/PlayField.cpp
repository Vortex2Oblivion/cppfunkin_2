#include "PlayField.hpp"

namespace funkin::objects::notes {
	PlayField::PlayField(const float x, const float y, const std::uint8_t keyCount, const float speed,
						 const std::vector<data::NoteData> &noteDatas, const std::shared_ptr<game::Conductor> &conductor) : Group(x, y) {
		// ReSharper disable once CppVariableCanBeMadeConstexpr
		const std::vector binds = {KEY_D, KEY_F, KEY_J, KEY_K};
		for (std::uint8_t i = 0; i < keyCount; i++) {
			std::vector<data::NoteData> noteDatasToAdd = {};
			for (auto noteData: noteDatas) {
				if (noteData.lane == i) {
					noteDatasToAdd.push_back(noteData);
				}
			}
			const auto noteLane = std::make_shared<NoteLane>(i * 160 * 0.7, 0, noteDatasToAdd, i, conductor);
			noteLane->speed = speed;
			noteLane->bind = binds[i];
			add(noteLane);
		}
	}

	PlayField::~PlayField() = default;

	float PlayField::getAccuracy() const {
		float accuracy = 0.0f;
		for (const auto &lane: members) {
			accuracy += lane->accuracy;
		}
		accuracy /= static_cast<float>(members.size());
		return accuracy;
	}

	std::uint16_t PlayField::getMisses() const {
		std::uint16_t misses = 0;
		for (const auto &lane: members) {
			misses += lane->misses;
		}
		return misses;
	}

	std::int32_t PlayField::getScore() const {
		std::int32_t score = 0;
		for (const auto &lane: members) {
			score += lane->score;
		}
		return score;
	}

	bool PlayField::getBotplay() const { return botplay; }

	void PlayField::setBotplay(const bool value) {
		botplay = value;
		for (const auto &lane: members) {
			lane->botplay = value;
		}
	}
} // namespace funkin::objects::notes
