#include "Text.hpp"

namespace funkin {
	std::unordered_map<std::string, Font> Text::fontCache = {};

	Text::Text(const float x, const float y, const std::string& text) : Sprite(x, y){
		this->text = text;
	}

	Text::~Text() = default;

	void Text::loadFont(const std::string &path) {
		if (fontCache.contains(path)) {
			_font = fontCache[path];
			return;
		}
		if (FileExists(path.c_str())) {
			fontCache[path] = LoadFont(path.c_str());
			loadFont(path);
		}
	}

	void Text::draw(float x, float y, const std::shared_ptr<Camera> cam) {
		DrawTextPro(_font, text.c_str(), position, origin, angle, size, spacing, color);
	}
} // funkin