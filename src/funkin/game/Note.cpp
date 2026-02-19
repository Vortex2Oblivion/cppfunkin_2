#include "Note.hpp"

namespace funkin::game {

	float Note::pixelsPerMS = 0.45f;

	Note::Note(const float strumTime, const std::uint8_t lane, const float speed) : Sprite(0.0f, 0.0f) {
		this->strumTime = strumTime;
		this->lane = lane;
		this->speed = speed;
	}
	Note::~Note() = default;
	void Note::updateY(const float songPosition, const float targetY) {
		position.y = targetY - pixelsPerMS * (songPosition - strumTime) * speed;
	}
}
