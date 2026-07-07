#pragma once

#include <memory>
#include <string>

#include "Character.hpp"
#include "funkin/Group.hpp"

namespace funkin {
	namespace modding {
		class LuaScript;
	}
	class Sprite;
} // namespace funkin
namespace funkin::objects {
	class Stage : public Group<Sprite> {
	public:
		explicit Stage(const std::string &stageName, const std::shared_ptr<Character> &boyfriend = nullptr,
					   const std::shared_ptr<Character> &dad = nullptr);
		~Stage() override;

		std::shared_ptr<modding::LuaScript> script = nullptr;
		std::string stageName;

		template<typename T = Sprite>
		void add(std::shared_ptr<T> object) {
			Group::add(object);
		}
	};

} // namespace funkin::objects
