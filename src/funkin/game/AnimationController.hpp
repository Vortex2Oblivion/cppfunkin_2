#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "data/animation/Animation.hpp"
#include "pugixml.hpp"

namespace funkin::game {
	class AnimationController {
		public:
			AnimationController();
			~AnimationController();

			std::unordered_map<std::string, std::shared_ptr<data::animation::Animation>> animations = {};
			std::unordered_map<std::string, Vector2> animationOffsets = {};
			std::shared_ptr<data::animation::Animation> currentAnimation = nullptr;

			void loadSparrow(const std::string& path);
			void loadPacker(const std::string& path);
			void addByPrefix(const std::string& name, const std::string &prefix, uint8_t framerate = 24, bool looped = false, const std::vector<std::uint8_t>& indices = {});
			void addOffset(const std::string& name, float x, float y);
			void addOffset(const std::string& name, Vector2 offset);
			void play(const std::string &name, bool force = false);
			void update(float delta) const;

			bool isFinished() const;
		protected:
			pugi::xml_document xmlDoc;
			pugi::xml_parse_result xmlParseResult;
			std::vector<data::animation::Frame> framesData = {};
	};
}
