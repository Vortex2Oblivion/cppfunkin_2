#include "Note.hpp"

namespace funkin::game {

	float Note::pixelsPerMS = 0.45f;

	Note::Note(const float strumTime, const std::uint8_t lane, const float speed, const bool sustainNote) : Sprite(0.0f, 0.0f) {
		this->strumTime = strumTime;
		this->lane = lane;
		this->speed = speed;
		this->sustainNote = sustainNote;

		if (!sustainNote) {
			loadTexture("assets/images/slungus.png");
		}
		else {
			loadTexture("assets/images/noteskins/funkin/sustains.png");
		}
	}
	Note::~Note() = default;
	void Note::updateY(const float songPosition, const float targetY) {
		position.y = targetY - pixelsPerMS * (songPosition - strumTime) * speed;
	}
}
