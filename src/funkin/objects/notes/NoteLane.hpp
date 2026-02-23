#pragma once

#include "Conductor.hpp"
#include "Group.hpp"
#include "Note.hpp"
#include "Sprite.hpp"
#include "StrumNote.hpp"
#include "data/Song.hpp"


namespace funkin::objects::notes {
	class NoteLane : public Group<> {
		friend class PlayField;

	public:
		NoteLane(float x, float y, const std::vector<data::NoteData> &noteDatas, std::uint8_t lane, const std::shared_ptr<game::Conductor> &conductor);
		~NoteLane() override;

		bool botplay = false;
		bool pressed = false;
		bool held = false;
		KeyboardKey bind = KEY_NULL;

		float speed = 1.0f;
		float accuracy = 0.0f;
		std::uint16_t lane = 0;
		std::uint16_t misses = 0;
		std::int32_t score = 0;
		float health = 50.0f;

		float minHitTime = 180.0f;
		float maxHitTime = 180.0f;

		float spawnTime = 2000.0f;

		std::shared_ptr<Group<Note>> notes;
		std::shared_ptr<StrumNote> strum;
		std::vector<std::shared_ptr<Note>> toInvalidate = {};

		void update(float delta) override;

	protected:
		std::vector<data::NoteData> noteDatas;
		std::uint16_t noteDataIndex = 0;
		std::shared_ptr<game::Conductor> conductor = nullptr;
	};
}