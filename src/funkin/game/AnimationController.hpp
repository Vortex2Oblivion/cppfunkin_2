#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "funkin/data/animation/Animation.hpp"
#include "raylib.h"

namespace funkin {
	class Sprite;
}
namespace funkin::game {
	class AnimationController {
	public:
		explicit AnimationController(Sprite *parent);
		~AnimationController();

		std::unordered_map<std::string, std::shared_ptr<data::animation::Animation>> animations = {};
		std::unordered_map<std::string, Vector2> animationOffsets = {};
		std::shared_ptr<data::animation::Animation> currentAnimation = nullptr;

		void loadSparrow(const std::string &path);
		void loadPacker(const std::string &path);
		void addByRects(const std::string &name, const std::vector<Rectangle> &rects, uint8_t framerate = 24, bool looped = false);
		void addByPrefix(const std::string &name, const std::string &prefix, uint8_t framerate = 24, bool looped = false,
						 const std::vector<std::uint8_t> &indices = {});
		void addOffset(const std::string &name, float x, float y);
		void addOffset(const std::string &name, Vector2 offset);
		void play(const std::string &name, bool force = false);
		void update(float delta) const;

		bool isFinished() const;
		static void clearFramesDataCache();

	protected:
		std::vector<data::animation::Frame> framesData = {};
		static std::unordered_map<std::string, std::vector<data::animation::Frame>> framesDataCache;
		Sprite *parent = nullptr;

		void updateParentHitbox() const;
	};
} // namespace funkin::game
