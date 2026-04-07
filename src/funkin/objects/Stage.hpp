#pragma once

#include "Character.hpp"
#include "Game.hpp"
#include "Group.hpp"
#include "LuaScript.hpp"
#include "Sprite.hpp"

namespace funkin::objects {
	class Stage : public Group<Sprite> {
	public:
		explicit Stage(const std::string &stageName, const std::shared_ptr<Character>& boyfriend = nullptr, const std::shared_ptr<Character>& dad = nullptr);
		~Stage() override;

		std::shared_ptr<modding::LuaScript> script = nullptr;
		std::string stageName;

		template<typename T = Sprite>
		void add(std::shared_ptr<T> object) {
			Group::add(object);
		}
	};

} // namespace funkin::objects
