#pragma once

#include <memory>
#include <type_traits>
#include <vector>

#include "Object.hpp"

namespace funkin {
	template<typename T>
	concept IsObject = std::is_base_of_v<Object, T>;

	template<IsObject T = Object>
	class Group : public Object {
	public:
		explicit Group(float X = 0.0f, float Y = 0.0f);

		~Group() override;

		void add(std::shared_ptr<T> object);
		void remove(std::shared_ptr<T> object);

		void draw(float x = 0.0f, float y = 0.0f) override;

		void update(float delta) override;

		std::vector<std::shared_ptr<T> > members = {};
	};

	template<IsObject T>
	Group<T>::Group(const float X, const float Y) : Object(X, Y) {}

	template<IsObject T>
	Group<T>::~Group() {
		members.clear();
	}

	template<IsObject T>
	void Group<T>::add(std::shared_ptr<T> object) {
		members.push_back(object);
	}

	template<IsObject T>
	void Group<T>::remove(std::shared_ptr<T> object) {
		members.erase(std::ranges::find(members, object));
	}

	template<IsObject T>
	void Group<T>::draw(const float x, const float y) {
		for (auto member: members) {
			if (member != nullptr) {
				member->draw(x + position.x, y + position.y);
			}
		}
	}

	template<IsObject T>
	void Group<T>::update(float delta) {
		for (auto member: members) {
			if (member != nullptr) {
				member->update(delta);
			}
		}
	}
}