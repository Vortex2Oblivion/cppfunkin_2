#pragma once

#include <cstdint>
#include "Sprite.hpp"
#include "StrumNote.hpp"

namespace funkin::objects::notes {
	class Note : public Sprite {
		public:
			Note(float strumTime, std::uint8_t lane, float speed, bool sustainNote = false, float sustainLength = 0.0f);

			~Note() override;

			float speed = 1.0f;
			float strumTime = 0.0f;
			float sustainLength = 0.0f;
			std::uint8_t lane = 0;
			bool sustainNote = false;
			bool wasHit = false;

			static float pixelsPerMS;

			std::shared_ptr<StrumNote> clipStrum = nullptr;
			std::shared_ptr<Note> parentNote = nullptr;

			void updateY(float songPosition, float targetY);
			void setupSustain(const std::shared_ptr<Note> &parent, const std::shared_ptr<StrumNote> &strum);
			void draw(float x, float y, std::shared_ptr<Camera> cam) override;
	};
}