#include "Sprite.hpp"

namespace funkin {
	Sprite::Sprite(const float x, const float y) : Object(x, y) {
		texture = LoadTexture("assets/images/noteskins/funkin/NOTE_hold_assets.png");
	}


	Sprite::~Sprite() = default;

	void Sprite::draw(const float x, const float y) {
		Object::draw(x, y);
		const float width = texture.width;
		const float height = texture.height;
		TraceLog(LOG_ALL, "akjshgdfaskhjljkhdlf");
		DrawTexturePro(texture,
			Rectangle{.x = 0, .y = 0, .width = width, .height = height},
			Rectangle{.x = position.x + x, .y = position.y + y, .width = width, .height = height}, Vector2Zero(), 0, WHITE);
	}
} // funkin