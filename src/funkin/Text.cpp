#include "Text.hpp"

#include "rlgl.h"

namespace funkin {
	std::unordered_map<std::string, Font> Text::fontCache = {};

	Text::Text(const float x, const float y, const std::string &text) : Sprite(x, y) { setText(text); }

	Text::~Text() = default;

	std::string Text::getText() { return text; }

	void Text::setText(const std::string &newText) {
		this->text = newText;
		updateHitbox();
	}

	void Text::updateHitbox() {
		const Vector2 textSize = MeasureTextEx(font, getText().c_str(), size, spacing);
		hitbox.width = (textSize * scale).x;
		hitbox.height = (textSize * scale).y;
		centerOrigin();
	}


	void Text::loadFont(const std::string &path) {
		if (fontCache.contains(path)) {
			font = fontCache[path];
			return;
		}
		if (FileExists(path.c_str())) {
			fontCache[path] = LoadFont(path.c_str());
			loadFont(path);
			updateHitbox();
		}
	}

	void Text::draw(float x, float y, const std::shared_ptr<Camera> cam) {
		rlPushMatrix();
		rlTranslatef(position.x + origin.x, position.y + origin.y, 0.0f);
		rlScalef(scale.x, scale.y, 1.0f);

		if (borderSize != 0.0f) {
			DrawTextPro(font, text.c_str(), (Vector2) {.x = borderSize, .y = 0.0f}, origin, angle, size, spacing, borderColor);
			DrawTextPro(font, text.c_str(), (Vector2) {.x = borderSize, .y = borderSize}, origin, angle, size, spacing, borderColor);
			DrawTextPro(font, text.c_str(), (Vector2) {.x = 0.0f, .y = borderSize}, origin, angle, size, spacing, borderColor);
			DrawTextPro(font, text.c_str(), (Vector2) {.x = -borderSize, .y = -borderSize}, origin, angle, size, spacing, borderColor);
			DrawTextPro(font, text.c_str(), (Vector2) {.x = borderSize, .y = -borderSize}, origin, angle, size, spacing, borderColor);
			DrawTextPro(font, text.c_str(), (Vector2) {.x = -borderSize, .y = borderSize}, origin, angle, size, spacing, borderColor);
			DrawTextPro(font, text.c_str(), (Vector2) {.x = -borderSize, .y = 0.0f}, origin, angle, size, spacing, borderColor);
			DrawTextPro(font, text.c_str(), (Vector2) {.x = 0.0f, .y = -borderSize}, origin, angle, size, spacing, borderColor);
		}

		DrawTextPro(font, text.c_str(), Vector2Zero(), origin, angle, size, spacing, color);

		rlPopMatrix();
	}
} // namespace funkin
