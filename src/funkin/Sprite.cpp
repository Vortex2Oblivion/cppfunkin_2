#include "Sprite.hpp"

#include <iostream>

#include "Game.hpp"


namespace funkin {
	std::unordered_map<std::string, Texture> Sprite::textureCache = {};

	Sprite::Sprite(const float x, const float y) : Object(x, y) {
	}

	Sprite::~Sprite() = default;

	bool Sprite::loadTexture(const std::string &path) {
		if (textureCache.contains(path)) {
			texture = textureCache[path];
			source = {
				.x = 0.0f, .y = 0.0f, .width = static_cast<float>(texture.width),
				.height = static_cast<float>(texture.height)
			};
			hitbox = {
				.x = 0.0f, .y = 0.0f, .width = static_cast<float>(texture.width),
				.height = static_cast<float>(texture.height)
			};
			return true;
		}
		if (FileExists(path.c_str())) {
			textureCache[path] = LoadTexture(path.c_str());
			SetTextureFilter(textureCache[path], TEXTURE_FILTER_BILINEAR);
			loadTexture(path);
			return true;
		}
		return false;
	}

	void Sprite::updateHitbox() {
		if (animation.currentAnimation != nullptr) {
			hitbox.width = animation.currentAnimation->frames[animation.currentAnimation->currentFrame].dest.width * scale.x;
			hitbox.height = animation.currentAnimation->frames[animation.currentAnimation->currentFrame].dest.height * scale.y;
		}
	}

	void Sprite::centerOffsets() {
		if (animation.currentAnimation != nullptr) {
			auto [source, dest] = animation.currentAnimation->frames[animation.currentAnimation->currentFrame];
			offset.x = -(dest.width - hitbox.width) / 2;
			offset.y = -(dest.height - hitbox.height) / 2;
		}
	}

	void Sprite::update(const float delta) {
		Object::update(delta);
		animation.update(delta);
	}


	void Sprite::draw(const float x, const float y) {
		Object::draw(x, y);
		if (texture.width <= 0 || texture.height <= 0) {
			return;
		}
		Rectangle dest = {.x = position.x + offset.x + x, .y = position.y + offset.y + y, .width = source.width * scale.x, .height = source.height * scale.y};
		if (animation.currentAnimation != nullptr) {
			auto frame = animation.currentAnimation->frames[animation.currentAnimation->currentFrame];
			source = frame.source;
			dest.width = frame.source.width * scale.x;
			dest.height = frame.source.height * scale.y;
			dest.x += frame.dest.x * scale.x;
			dest.y += frame.dest.y * scale.y;
		}
		DrawTexturePro(texture, source, dest, origin, angle, ColorAlpha(color, alpha));
		if (drawHitbox) {
			DrawRectanglePro(Rectangle{.x = hitbox.x + position.x + x, .y = hitbox.y + position.y + y, .width = hitbox.width, .height = hitbox.height }, origin, angle, ColorAlpha(hitboxColor, 0.5f * alpha));
		}
	}
} // funkin