#pragma once

#include "NoteLane.hpp"
#include "funkin/Group.hpp"
#include "funkin/data/Song.hpp"

namespace funkin::objects::notes {
	class NoteLane;
	class PlayField : public Group<NoteLane> {
		friend class NoteLane;

	public:
		explicit PlayField(float x = 0.0f, float y = 0.0f, std::uint8_t keyCount = 4, float speed = 1.0f,
						   const std::vector<data::NoteData> &noteDatas = {}, const std::shared_ptr<game::Conductor> &conductor = nullptr);

		~PlayField() override;

		float health = 50.0f;

		float accuracy = 100.0f;

		Vector2 scale = Vector2One();
		Vector2 skew = Vector2Zero();
		Vector2 origin = Vector2Zero();

		[[nodiscard]] std::uint16_t getMisses() const;
		[[nodiscard]] std::int32_t getScore() const;
		[[nodiscard]] bool getBotplay() const;
		void setBotplay(bool value);

		void draw(float x, float y, const std::shared_ptr<Camera> &cam) override;

	protected:
		bool botplay = false;
		void calculateAccuracy();

		std::size_t interactedNotes = 0;
		float notesHit = 0;
	};
} // namespace funkin::objects::notes
