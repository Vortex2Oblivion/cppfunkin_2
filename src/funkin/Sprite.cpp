#include "Sprite.hpp"

namespace funkin {
	std::unordered_map<std::string, Texture> Sprite::textureCache = {};

	Sprite::Sprite(const float x, const float y) : Object(x, y) {}

	Sprite::~Sprite() = default;

	bool Sprite::loadTexture(const std::string& path) {
		if (textureCache.contains(path)) {
			texture = textureCache[path];
			source = {.x = 0.0f, .y = 0.0f, .width = static_cast<float>(texture.width), .height = static_cast<float>(texture.height)};
			return true;
		}
		if (FileExists(path.c_str())) {
			textureCache[path] = LoadTexture(path.c_str());
			loadTexture(path);
			return true;
		}
		return false;
	}

	void Sprite::draw(const float x, const float y) {
		Object::draw(x, y);
		if (texture.width <= 0 && texture.height <= 0) {
			return;
		}
		DrawTexturePro(texture,
			source,
			Rectangle{.x = position.x + x, .y = position.y + y, .width = source.width * scale.x, .height = source.height * scale.y}, origin, angle, color);
	}
} // funkin