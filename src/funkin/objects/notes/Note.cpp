#include "Note.hpp"

namespace funkin::objects::notes {
	float Note::pixelsPerMS = 0.45f;

	Note::Note(const float strumTime, const std::uint8_t lane, const float speed, const bool sustainNote,
			   const float sustainLength) : Sprite(0.0f, 0.0f) {
		this->strumTime = strumTime;
		this->lane = lane;
		this->speed = speed;
		this->sustainNote = sustainNote;
		this->sustainLength = sustainLength;

		const std::vector<std::string> colors = {"purple", "blue", "green", "red"};

		if (!sustainNote) {
			loadTexture("assets/images/noteskins/funkin/notes.png");
			animation.loadSparrow("assets/images/noteskins/funkin/notes.xml");
			animation.addByPrefix("note", colors[lane % colors.size()], 0);
			animation.play("note");
		} else {
			loadTexture("assets/images/noteskins/funkin/sustains.png");
		}
	}

	Note::~Note() = default;

	void Note::updateY(const float songPosition, const float targetY) {
		position.y = targetY - pixelsPerMS * (songPosition - strumTime) * speed;
		if (parentNote != nullptr) {
			position.y += parentNote->dest.height / 2.0f;
		}
	}

	void Note::draw(const float x, const float y, const std::shared_ptr<Camera> cam) {
		// ReSharper disable once CppRedundantComplexityInComparison
		const bool shouldScissor = sustainNote && !(clipStrum == nullptr);
		if (shouldScissor) {
			const int yScissor = static_cast<int>(cam->getWorldToScreen(Vector2{.x = x, .y = clipStrum->position.y + clipStrum->hitbox.height / 2 + y}).y);
			BeginScissorMode(0, yScissor, GetRenderWidth(), GetRenderHeight() - yScissor);
		}

		Sprite::draw(x, y, cam);

		if (shouldScissor) {
			EndScissorMode();
		}
	}
} // namespace funkin::objects::notes
