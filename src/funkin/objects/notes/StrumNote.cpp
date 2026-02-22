#include "StrumNote.hpp"

namespace funkin::objects::notes {
	StrumNote::StrumNote(const std::uint8_t lane) : Sprite(0.0f, 0.0f) {
		this->lane = lane;
		const std::vector<std::string> colors = {"left", "down", "up", "right"};
		loadTexture("assets/images/noteskins/funkin/strums.png");
		animation.loadSparrow("assets/images/noteskins/funkin/strums.xml");
		animation.addByPrefix("static", colors[lane % colors.size()] + " static", 0);
		animation.addByPrefix("press", colors[lane % colors.size()] + " press", 24);
		animation.addByPrefix("confirm", colors[lane % colors.size()] + " confirm", 24);
		animation.play("static");
		updateHitbox();
		drawHitbox = true;
	}

	StrumNote::~StrumNote() = default;
}
