#pragma once
#include "Group.hpp"
#include "NoteLane.hpp"

namespace funkin::objects::notes {
	class PlayField : public Group<NoteLane> {
	public:
		PlayField(float x, float y, std::uint8_t keyCount, float speed,
		          const std::vector<data::NoteData> &noteDatas,
		          const std::shared_ptr<game::Conductor> &conductor);

		~PlayField() override;
	};
}