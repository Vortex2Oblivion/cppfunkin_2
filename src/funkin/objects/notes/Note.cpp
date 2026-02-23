#include "Note.hpp"

namespace funkin::objects::notes {
	float Note::pixelsPerMS = 0.45f;

	Note::Note(const float strumTime, const std::uint8_t lane, const float speed, const bool sustainNote) : Sprite(
		0.0f, 0.0f) {
		this->strumTime = strumTime;
		this->lane = lane;
		this->speed = speed;
		this->sustainNote = sustainNote;

		const std::vector<std::string> colors = {"purple", "blue", "green", "red"};

		if (!sustainNote) {
			loadTexture("assets/images/noteskins/funkin/notes.png");
			animation.loadSparrow("assets/images/noteskins/funkin/notes.xml");
			animation.addByPrefix("note", colors[lane % colors.size()], 0);
			animation.play("note");
			updateHitbox();
			centerOffsets();
		} else {
			loadTexture("assets/images/noteskins/funkin/sustains.png");
		}
	}

	Note::~Note() = default;

	void Note::updateY(const float songPosition, const float targetY) {
		position.y = targetY - pixelsPerMS * (songPosition - strumTime) * speed;
	}
}