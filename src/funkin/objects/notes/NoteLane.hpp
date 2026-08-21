#pragma once

#include <memory>
#include <vector>

#include "Note.hpp"
#include "eventpp/callbacklist.h"
#include "funkin/Group.hpp"
#include "funkin/data/Song.hpp"
#include "funkin/game/Conductor.hpp"
#include "raylib.h"

namespace funkin::objects::notes {
	class PlayField;
	class NoteLane : public Group<> {
		friend class PlayField;

	public:
		NoteLane(float x, float y, const std::vector<data::NoteData> &noteDatas, std::uint8_t lane,
				 const std::shared_ptr<game::Conductor> &conductor, PlayField *parent = nullptr);
		~NoteLane() override;

		bool botplay = false;
		bool pressed = false;
		bool held = false;
		KeyboardKey bind = KEY_NULL;

		std::uint16_t lane = 0;

		float speed = 1.0f;
		float accuracy = 100.0f;
		std::uint16_t misses = 0;

		float score = 0; // calculated as a float internally

		float minHealth = 0.0f;
		float maxHealth = 100.0f;
		float health = Lerp(minHealth, maxHealth, 0.5);
		float healthMissPenalty = 4.0f;

		float minHitTime = 180.0f;
		float maxHitTime = 180.0f;

		float spawnTime = 2000.0f;

		float maxScore = 500;
		float holdScore = 250.0f;
		float holdHealthMultiplier = 0.06f;
		float scoreMissPenalty = 10;

		std::shared_ptr<Group<Note>> sustains;
		std::shared_ptr<Group<Note>> notes;
		std::shared_ptr<StrumNote> strum;
		std::vector<std::shared_ptr<Note>> toInvalidate = {};

		eventpp::CallbackList<void(std::shared_ptr<Note>)> onNoteHit;
		eventpp::CallbackList<void(std::shared_ptr<Note>)> onNoteMiss;

		void update(float delta) override;

	protected:
		std::uint16_t noteDataIndex = 0;
		std::vector<data::NoteData> noteDatas;
		std::size_t interactedNotes = 0;
		float notesHit = 0;

		std::shared_ptr<game::Conductor> conductor = nullptr;
		PlayField *parent = nullptr;

		void calculateAccuracy();
	};
} // namespace funkin::objects::notes
