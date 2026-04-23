#include "AnimationController.hpp"

#include <iomanip>
#include <iostream>
#include <ranges>

#include "CoolUtil.hpp"
#include "raylib.h"
#include "raymath.h"
#include "boost/algorithm/string.hpp"

namespace funkin::game {
	AnimationController::AnimationController() = default;

	AnimationController::~AnimationController() {
		animations.clear();
	}

	void AnimationController::loadSparrow(const std::string& path) {
		framesData.clear();
		if (!FileExists(path.c_str())) {
			return;
		}
		xmlParseResult = xmlDoc.load_file(path.c_str());

		if (!xmlParseResult) {
			return;
		}

		for (auto frame : xmlDoc.child("TextureAtlas").children("SubTexture")) {
			const std::string animationName = frame.attribute("name").as_string();
			const bool trimmed = frame.attribute("frameX");

			const float x = frame.attribute("x").as_float();
			const float y = frame.attribute("y").as_float();
			const float width = frame.attribute("width").as_float();
			const float height = frame.attribute("height").as_float();
			const float frameX = frame.attribute("frameX").as_float();
			const float frameY = frame.attribute("frameY").as_float();
			const float frameWidth = frame.attribute("frameWidth").as_float();
			const float frameHeight = frame.attribute("frameHeight").as_float();

			const auto [offsetX, offsetY] = trimmed ? Vector2{.x = -frameX, .y = -frameY} : Vector2Zero();
			const auto [sourceWidth, sourceHeight] = trimmed ? Vector2{.x = frameWidth, .y = frameHeight} : Vector2{.x = width, .y = height};
			framesData.push_back(data::animation::Frame{
				.source = Rectangle{.x = x, .y = y, .width = width, .height = height},
				.dest = Rectangle{.x = offsetX, .y = offsetY, .width = sourceWidth, .height = sourceHeight},
				.name = animationName
			});
		}

	}

	void AnimationController::loadPacker(const std::string& path) {
		framesData.clear();
		if (!FileExists(path.c_str())) {
			return;
		}
		const auto fileContent = LoadFileText(path.c_str());
		std::vector<std::string> lines;
		boost::split(lines, fileContent, boost::is_any_of("\n"));
		for (auto line : lines) {
			std::vector<std::string> currentFrameData;
			boost::split(currentFrameData, line, boost::is_any_of("="));

			std::string name = currentFrameData[0];
			boost::trim(name);

			std::string framesDataStr = currentFrameData.size() >= 2 ? currentFrameData[1] : "";
			boost::trim(framesDataStr);

			std::vector<std::string> rectData;
			boost::split(rectData, framesDataStr, boost::is_any_of(" "));

			// fix wierd crash when going out of bounds sometimes
			if (rectData.size() < 4) {
				continue;
			}

			const float x = std::stof(rectData[0]);
			const float y = std::stof(rectData[1]);
			const float width = std::stof(rectData[2]);
			const float height = std::stof(rectData[3]);

			framesData.push_back(data::animation::Frame{
				.source = Rectangle{.x = x, .y = y, .width = width, .height = height},
				.dest = {.x = 0.0f, .y = 0.0f, .width = width, .height = height},
				.name = name}
				);
		}
	}


	void AnimationController::addByPrefix(const std::string& name, const std::string& prefix, const std::uint8_t framerate, const bool looped, const std::vector<std::uint8_t>& indices) {
		std::vector<data::animation::Frame> frames = {};
		std::uint8_t frameIndex = 0;

		if (framesData.empty()) {
			return;
		}

		for (const auto& frame : framesData) {
			if (!frame.name.starts_with(prefix)) { // find all animations that start with `prefix`
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

			frames.push_back(frame);
		}

		animations[name] = std::make_shared<data::animation::Animation>(frames, name, framerate, looped);
		animationOffsets[name] = Vector2Zero();
	}

	void AnimationController::addOffset(const std::string& name, const float x, const float y) {
		addOffset(name, Vector2{.x = x, .y = y});
	}

	void AnimationController::addOffset(const std::string& name, const Vector2 offset) {
		animationOffsets[name] = offset;
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

	bool AnimationController::isFinished() const {
		if (currentAnimation != nullptr) {
			return currentAnimation->currentFrame + 1 >= currentAnimation->frames.size();
		}
		return false;
	}
} // namespace funkin::game
