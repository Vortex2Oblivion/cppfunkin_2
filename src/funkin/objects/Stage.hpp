#pragma once

#include <memory>
#include <string>

#include "Character.hpp"
#include "funkin/Group.hpp"


namespace funkin::objects {
	class Stage : public Group<Sprite> {
	public:
		explicit Stage(const std::string &stageName, const std::shared_ptr<Character> &boyfriend = nullptr,
					   const std::shared_ptr<Character> &dad = nullptr, const std::shared_ptr<Character> &girlfriend = nullptr);
		~Stage() override;

		std::shared_ptr<modding::LuaScript> script = nullptr;
		std::string stageName;

		static void snapToPosition(const std::shared_ptr<Character>& character, float x, float y);

		template<typename T = Sprite>
		void add(std::shared_ptr<T> object) {
			Group::add(object);
		}
	};

} // namespace funkin::objects
