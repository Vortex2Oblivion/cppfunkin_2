#pragma once

#include "funkin/Sprite.hpp"


namespace funkin::objects::notes {
	class StrumNote : public Sprite {
		public:
			explicit StrumNote(uint8_t lane);
			~StrumNote() override;

			uint8_t lane = 0;
	};
}