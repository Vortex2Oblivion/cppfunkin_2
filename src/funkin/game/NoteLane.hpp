#pragma once

#include "Conductor.hpp"
#include "Group.hpp"
#include "Note.hpp"
#include "Sprite.hpp"
#include "StrumNote.hpp"
#include "data/Song.hpp"


namespace funkin::game {
	class NoteLane : public Group<> {
		friend class PlayField;
		public:
			NoteLane(float x, float y, const std::vector<data::NoteData>& noteDatas, const std::shared_ptr<Conductor>& conductor);
			~NoteLane() override;

			KeyboardKey bind = KEY_NULL;

			bool botplay = false;
			float speed = 1.0f;
			float accuracy = 0.0f;
			uint16_t misses = 0;
			int32_t score = 0;
			float health = 50.0f;

			float minHitTime = 180.0f;
			float maxHitTime = 180.0f;

			float spawnTime = 2000.0f;

			std::shared_ptr<Group<Note>> notes;
		std::shared_ptr<StrumNote> strum;

			void update(float delta) override;
		protected:
			std::vector<data::NoteData> noteDatas;
			uint16_t noteDataIndex = 0;
			std::shared_ptr<Conductor> conductor = nullptr;
	};
}
