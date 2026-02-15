#pragma once

#include <type_traits>
#include <vector>

#include "Object.hpp"

namespace funkin {

	template<typename T>
	concept IsObject = std::is_base_of_v<Object, T>;

	template <IsObject T = Object>
	class Group : public Object {
		public:
			explicit Group(float X = 0.0f, float Y = 0.0f);
			~Group();

			void add(T object);
			void draw(float x, float y);
			void update(float delta);

			std::vector<T> members = {};
	};

	template <IsObject T>
	Group<T>::Group(const float X, const float Y) : Object(X, Y) {}

	template <IsObject T>
	Group<T>::~Group() {
		members.clear();
	}


	template <IsObject T>
	void Group<T>::add(T object) {
		members.push_back(object);
	}

	template <IsObject T>
	void Group<T>::draw(float x, float y) {
		for (auto member : members) {
			member->draw(x, y);
		}
	}

	template <IsObject T>
	void Group<T>::update(float delta) {
			for (auto member : members) {
				member.update(delta);
			}
		}
}

