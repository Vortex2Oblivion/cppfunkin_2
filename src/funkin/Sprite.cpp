#include "Sprite.hpp"

#include "Game.hpp"

namespace funkin {
	std::unordered_map<std::string, Texture> Sprite::textureCache = {};

	Sprite::Sprite(const float x, const float y) : Object(x, y) {}

	Sprite::~Sprite() = default;

	bool Sprite::loadTexture(const std::string &path) {
		if (textureCache.contains(path)) {
			texture = textureCache[path];
			source = {.x = 0.0f,
					  .y = 0.0f,
					  .width = static_cast<float>(texture.width),
					  .height = static_cast<float>(texture.height)};
			hitbox = {.x = 0.0f,
					  .y = 0.0f,
					  .width = static_cast<float>(texture.width),
					  .height = static_cast<float>(texture.height)};
			return true;
		}
		if (FileExists(path.c_str())) {
			textureCache[path] = LoadTexture(path.c_str());
			loadTexture(path);
			setAntialiasing(antialiasing);
			return true;
		}
		return false;
	}

	void Sprite::updateHitbox() {
		if (getCurrentAnimation() != nullptr && !getCurrentAnimation()->frames.empty()) {
			hitbox.width = getCurrentAnimation()->frames[getCurrentAnimation()->currentFrame].dest.width * scale.x;
			hitbox.height = getCurrentAnimation()->frames[getCurrentAnimation()->currentFrame].dest.height * scale.y;
		}
	}

	void Sprite::centerOffsets() {
		if (getCurrentAnimation() != nullptr && !getCurrentAnimation()->frames.empty()) {
			const auto _dest = getCurrentAnimation()->frames[getCurrentAnimation()->currentFrame].dest;
			offset.x = -(_dest.width - hitbox.width) / 2;
			offset.y = -(_dest.height - hitbox.height) / 2;
		}
	}

	void Sprite::setAntialiasing(const bool enable) const {
		if (enable) {
			SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
		} else {
			SetTextureFilter(texture, TEXTURE_FILTER_POINT);
		}
	}

	bool Sprite::getAntialiasing() const { return antialiasing; }

	void Sprite::update(const float delta) {
		Object::update(delta);
		animation.update(delta);
	}

	bool Sprite::isOnScreen(const std::shared_ptr<Camera> &cam) const {
		const auto [x, y] = cam->getWorldToScreen(Vector2{dest.x, dest.y});
		return x + dest.width > 0 && x < static_cast<float>(GetRenderWidth()) && y + dest.height > 0 &&
			   y < static_cast<float>(GetRenderHeight());
	}

	Vector2 Sprite::getMidpoint() const {
		return position + offset + Vector2{.x = hitbox.width / 2.0f, .y = hitbox.height / 2.0f} -
			   Vector2{.x = 1280.0 / 2, .y = 720.0 / 2};
	}

	std::shared_ptr<data::animation::Animation> Sprite::getCurrentAnimation() const {
		std::vector<data::animation::Frame> blankFrames = {};
		return animation.currentAnimation == nullptr
					   ? std::make_shared<data::animation::Animation>(blankFrames, "", 0)
					   : animation.currentAnimation;
	}

	void Sprite::draw(const float x, const float y, const std::shared_ptr<Camera> cam) {
		Object::draw(x, y, cam);

		if (texture.width <= 0 || texture.height <= 0) {
			return;
		}

		dest = {.x = position.x + offset.x + x,
				.y = position.y + offset.y + y,
				.width = source.width * scale.x,
				.height = source.height * scale.y};

		if (getCurrentAnimation() != nullptr && !getCurrentAnimation()->frames.empty()) {
			auto [_source, _dest, _name] = getCurrentAnimation()->frames[getCurrentAnimation()->currentFrame];
			this->source = _source;
			dest.width = source.width * scale.x;
			dest.height = source.height * scale.y;
			dest.x += _dest.x * scale.x;
			dest.y += _dest.y * scale.y;
			auto [_x, _y] = animation.animationOffsets[getCurrentAnimation()->name];
			dest.x -= _x;
			dest.y -= _y;
		}

		dest.x += -cam->target.x * (scrollFactor.x - 1.0f);
		dest.y += -cam->target.y * (scrollFactor.y - 1.0f);

		if (!isOnScreen(cam)) {
			return;
		}

		DrawTexturePro(texture, source, dest, origin, angle, ColorAlpha(color, alpha));
		if (drawHitbox) {
			DrawRectanglePro(Rectangle{.x = hitbox.x + position.x + x,
									   .y = hitbox.y + position.y + y,
									   .width = hitbox.width,
									   .height = hitbox.height},
							 origin, angle, ColorAlpha(hitboxColor, 0.5f * alpha));
		}
	}

	void Sprite::clearTextureCache() { textureCache.clear(); }
} // namespace funkin
