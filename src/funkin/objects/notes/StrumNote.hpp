#pragma once
#include "Sprite.hpp"

namespace funkin::objects::notes {
	class StrumNote : public Sprite {
		public:
			explicit StrumNote(std::uint8_t lane);
			~StrumNote() override;

			std::uint8_t lane = 0;
	};
}