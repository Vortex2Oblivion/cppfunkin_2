#include "AnimationController.hpp"

#include <iomanip>
#include <iostream>
#include <ranges>

#include "funkin/Sprite.hpp"
#include "funkin/data/animation/Animation.hpp"
#include "funkin/data/animation/Frame.hpp"
#include "funkin/utilities/CoolUtil.hpp"
#include "pugixml.hpp"
#include "raylib.h"
#include "raymath.h"

namespace funkin::game {
	std::unordered_map<std::string, std::vector<data::animation::Frame>> AnimationController::framesDataCache = {};

	AnimationController::AnimationController(Sprite *parent) { this->parent = parent; };

	AnimationController::~AnimationController() { animations.clear(); }

	void AnimationController::loadSparrow(const std::string &path) {
		framesData.clear();
		if (framesDataCache.contains(path)) {
			framesData = std::vector(framesDataCache[path]);
			updateParentHitbox();
			return;
		}
		if (!FileExists(path.c_str())) {
			return;
		}
		pugi::xml_document xmlDoc;
		const pugi::xml_parse_result xmlParseResult = xmlDoc.load_file(path.c_str());

		if (!xmlParseResult) {
			return;
		}

		for (auto frame: xmlDoc.child("TextureAtlas").children("SubTexture")) {
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
			const auto [sourceWidth, sourceHeight] =
					trimmed ? Vector2{.x = frameWidth, .y = frameHeight} : Vector2{.x = width, .y = height};
			framesData.push_back(
					data::animation::Frame{.source = Rectangle{.x = x, .y = y, .width = width, .height = height},
										   .dest = Rectangle{.x = offsetX, .y = offsetY, .width = sourceWidth, .height = sourceHeight},
										   .name = animationName});
		}
		framesDataCache[path] = std::vector(framesData);
		updateParentHitbox();
	}

	void AnimationController::loadPacker(const std::string &path) {
		framesData.clear();
		if (framesDataCache.contains(path)) {
			framesData = std::vector(framesDataCache[path]);
			updateParentHitbox();
			return;
		}
		if (!FileExists(path.c_str())) {
			return;
		}
		const auto fileContent = LoadFileText(path.c_str());
		const auto lines = utilities::CoolUtil::split(fileContent, "\n");
		for (const auto &line: lines) {
			std::cout << line << std::endl;

			auto currentFrameData = utilities::CoolUtil::split(line, "=");


			const std::string name = utilities::CoolUtil::trim(currentFrameData[0]);

			const std::string framesDataStr = utilities::CoolUtil::trim(currentFrameData.size() >= 2 ? currentFrameData[1] : "");

			auto rectData = utilities::CoolUtil::split(framesDataStr, " ");

			// fix wierd crash when going out of bounds sometimes
			if (rectData.size() < 4) {
				continue;
			}

			const float x = std::stof(rectData[0]);
			const float y = std::stof(rectData[1]);
			const float width = std::stof(rectData[2]);
			const float height = std::stof(rectData[3]);

			framesData.push_back(data::animation::Frame{.source = Rectangle{.x = x, .y = y, .width = width, .height = height},
														.dest = {.x = 0.0f, .y = 0.0f, .width = width, .height = height},
														.name = name});
		}
		framesDataCache[path] = std::vector(framesData);
		updateParentHitbox();
	}

	void AnimationController::addByRects(const std::string &name, const std::vector<Rectangle> &rects, uint8_t framerate, bool looped) {
		if (rects.empty()) {
			return;
		}

		std::vector<data::animation::Frame> frames = {};

		for (const auto rect: rects) {
			frames.push_back(data::animation::Frame{
					.source = rect, .dest = Rectangle{.x = 0.0f, .y = 0.0f, .width = rect.width, .height = rect.height}, .name = name});
		}

		animations[name] = std::make_shared<data::animation::Animation>(frames, name, framerate, looped);
		animationOffsets[name] = Vector2Zero();
	}


	void AnimationController::addByPrefix(const std::string &name, const std::string &prefix, const std::uint8_t framerate,
										  const bool looped, const std::vector<std::uint8_t> &indices) {
		std::vector<data::animation::Frame> frames = {};
		std::uint8_t frameIndex = 0;

		if (framesData.empty()) {
			return;
		}

		for (const auto &frame: framesData) {
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

	void AnimationController::addOffset(const std::string &name, const float x, const float y) { addOffset(name, Vector2{.x = x, .y = y}); }

	void AnimationController::addOffset(const std::string &name, const Vector2 offset) { animationOffsets[name] = offset; }

	void AnimationController::play(const std::string &name, bool force) {
		if (animations.empty() || !animations.contains(name)) {
			return;
		}
		if (currentAnimation == nullptr) {
			force = true;
		}
		if (!force && !currentAnimation->finished) {
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

	void AnimationController::updateParentHitbox() const {
		if (!framesData.empty()) {
			parent->hitbox.width = framesData[0].dest.width * parent->scale.x;
			parent->hitbox.height = framesData[0].dest.height * parent->scale.y;
		}
	}

	void AnimationController::clearFramesDataCache() { framesDataCache.clear(); }
} // namespace funkin::game
