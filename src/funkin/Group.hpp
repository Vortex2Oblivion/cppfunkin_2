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
			explicit Group(float x = 0.0f, float y = 0.0f);
			~Group();

			void Add(T object);
			void Draw(float x, float y);
			std::vector<T> members = {};
	};

	template <IsObject T>
	Group<T>::Group(const float x, const float y) : Object(x, y) {}

	template <IsObject T>
	Group<T>::~Group() {
		members.clear();
	}

	template <IsObject T>
	void Group<T>::Add(T object) {
		members.push_back(object);
	}

	template <IsObject T>
	void Group<T>::Draw(float x, float y) {
		for (auto member : members) {
			member->Draw(x, y);
		}
	}
}

