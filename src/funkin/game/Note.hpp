#pragma once

#include <cstdint>

#include "Sprite.hpp"

namespace funkin::game {
	class Note : public Sprite {
		public:
			Note(float strumTime, std::uint8_t lane, float speed, bool sustainNote = false);
			~Note() override;

			float speed = 1.0f;
			float strumTime = 0.0f;
			std::uint8_t lane = 0;
			bool sustainNote = false;

			static float pixelsPerMS;

			void updateY(float songPosition, float targetY);
	};
}
