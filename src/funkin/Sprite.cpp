#include "Sprite.hpp"

namespace funkin {
	std::unordered_map<std::string, Texture> Sprite::textureCache = {};

	Sprite::Sprite(const float x, const float y) : Object(x, y) {}

	Sprite::~Sprite() = default;

	bool Sprite::loadTexture(const std::string& path) {
		if (textureCache.contains(path)) {
			texture = textureCache[path];
			return true;
		}
		if (FileExists(path.c_str())) {
			texture = textureCache[path] = LoadTexture(path.c_str());
			return true;
		}
		return false;
	}

	void Sprite::draw(const float x, const float y) {
		Object::draw(x, y);
		if (texture.width <= 0 && texture.height <= 0) {
			return;
		}
		const float width = texture.width;
		const float height = texture.height;
		DrawTexturePro(texture,
			Rectangle{.x = 0, .y = 0, .width = width, .height = height},
			Rectangle{.x = position.x + x, .y = position.y + y, .width = width, .height = height}, Vector2Zero(), 0, WHITE);
	}
} // funkin