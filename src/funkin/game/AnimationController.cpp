#include "AnimationController.hpp"

#include <iostream>

#include "raylib.h"
#include "raymath.h"

namespace funkin::game {
	AnimationController::AnimationController() = default;

	AnimationController::~AnimationController() {
		animations.clear();
	}

	void AnimationController::loadSparrow(const std::string& path) {
		if (!FileExists(path.c_str())) {
			return;
		}
		xmlParseResult = xmlDoc.load_file(path.c_str());
	}

	void AnimationController::addByPrefix(const std::string& name, const std::string& prefix, const std::uint8_t framerate, const bool looped, const std::vector<std::uint8_t>& indices) {
		std::vector<data::animation::Frame> frames = {};

		if (!xmlParseResult) {
			return;
		}

		std::uint8_t frameIndex = 0;

		for (auto frame : xmlDoc.child("TextureAtlas").children("SubTexture")) {
			const std::string animationName = frame.attribute("name").as_string();
			if (!animationName.starts_with(prefix)) { // find all animations that start with `prefix`
				continue;
			}

			bool addFrame = true;

			if (!indices.empty()) {
				addFrame = std::ranges::find(indices, frameIndex) != indices.end();
			}

			frameIndex++;

			if (!addFrame) {
				continue;
			}

			const bool trimmed = frame.attribute("frameX");

			const float x = frame.attribute("x").as_float();
			const float y = frame.attribute("y").as_float();
			const float width = frame.attribute("width").as_float();
			const float height = frame.attribute("height").as_float();
			const float frameX = frame.attribute("frameX").as_float();
			const float frameY = frame.attribute("frameY").as_float();
			const float frameWidth = frame.attribute("frameWidth").as_float();
			const float frameHeight = frame.attribute("frameHeight").as_float();

			const Vector2 offset = trimmed ? Vector2{.x = -frameX, .y = -frameY} : Vector2Zero();
			const Vector2 sourceSize = trimmed ? Vector2{.x = frameWidth, .y = frameHeight} : Vector2{.x = width, .y = height};
			frames.push_back(data::animation::Frame{
				.source = Rectangle{.x = x, .y = y, .width = width, .height = height},
				.dest = Rectangle{.x = offset.x, .y = offset.y, .width = sourceSize.x, .height = sourceSize.y
				}});
		}

		animations[name] = std::make_shared<data::animation::Animation>(frames, framerate, looped);
	}

	void AnimationController::play(const std::string& name) {
		if (animations.empty() || !animations.contains(name)) {
			return;
		}
		currentAnimation = animations[name];
		currentAnimation->resetFrame();
	}

	void AnimationController::update(const float delta) const {
		if (currentAnimation != nullptr) {
			currentAnimation->update(delta);
		}
	}
}
