#include "Text.hpp"

#include <functional>
#include <ranges>
#include "rlgl.h"

namespace funkin {
	std::unordered_map<std::filesystem::path, Font> Text::fontCache = {};

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


	void Text::loadFont(const std::filesystem::path &path) {
		if (fontCache.contains(path)) {
			font = fontCache[path];
			return;
		}
		if (FileExists(path.string().c_str())) {
			fontCache[path] = LoadFont(path.string().c_str());
			loadFont(path);
			updateHitbox();
		}
	}

	void Text::draw(float x, float y, const std::shared_ptr<Camera> &cam) {
		rlPushMatrix();
		rlTranslatef(position.x + origin.x, position.y + origin.y, 0.0f);
		rlScalef(scale.x, scale.y, 1.0f);

		if (borderSize != 0.0f) {
			for (uint8_t i = 0; i < 8; i++) {
				auto _borderSize = borderSize;

				if (i % 2 == 1) {
					_borderSize = hypot(borderSize, borderSize);
				}

				const float rad = static_cast<float>(i) / 8.0f * PI * 2.0f;

				DrawTextPro(font, text.c_str(), Vector2{.x = cos(rad) * _borderSize, .y = sin(rad) * _borderSize}, origin, angle, size,
							spacing, borderColor);
			}
		}

		DrawTextPro(font, text.c_str(), Vector2Zero(), origin, angle, size, spacing, color);

		rlPopMatrix();
	}

	void Text::clearFontCache() {
		for (const auto &val: fontCache | std::views::values) {
			UnloadFont(val);
		}
		fontCache.clear();
	}
} // namespace funkin
