#pragma once

#include "NoteLane.hpp"
#include "funkin/Group.hpp"
#include "funkin/data/Song.hpp"

namespace funkin::objects::notes {
	class PlayField : public Group<NoteLane> {
		public:
			explicit PlayField(float x = 0.0f, float y = 0.0f, std::uint8_t keyCount = 4, float speed = 1.0f,
		          const std::vector<data::NoteData> &noteDatas = {},
		          const std::shared_ptr<game::Conductor> &conductor = nullptr);

			~PlayField() override;

			bool getBotplay() const;
			void setBotplay(bool value);
		protected:
			bool botplay = false;
	};
}