#pragma once

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>
#include "Object.hpp"
#include "Sprite.hpp"

namespace funkin {
	template<typename T>
	concept IsObject = std::is_base_of_v<Object, T>;
	template<IsObject T = Object>
	class Group : public Sprite {
	public:
		explicit Group(float x = 0.0f, float y = 0.0f);
		~Group() override;

		void add(std::shared_ptr<T> object);
		void remove(std::shared_ptr<T> object);
		void clear();

		std::size_t size();

		void draw(float x, float y, const std::shared_ptr<Camera> &cam) override;

		void update(float delta) override;

		std::vector<std::shared_ptr<T>> members = {};
	};

	template<IsObject T>
	Group<T>::Group(const float x, const float y) : Sprite(x, y) {}


	template<IsObject T>
	Group<T>::~Group() {
		if (!WindowShouldClose()) {
			members.clear();
		}
	}

	template<IsObject T>
	void Group<T>::add(std::shared_ptr<T> object) {
		members.push_back(object);
	}

	template<IsObject T>
	void Group<T>::remove(std::shared_ptr<T> object) {
		if (auto ranges = std::ranges::find(members, object); ranges != members.end()) {
			members.erase(ranges);
		}
	}

	template<IsObject T>
	void Group<T>::clear() {
		members.clear();
	}

	template<IsObject T>
	std::size_t Group<T>::size() {
		return members.size();
	}

	template<IsObject T>
	void Group<T>::draw(const float x, const float y, const std::shared_ptr<Camera> &cam) {
		for (auto member: members) {
			if (member != nullptr) {
				member->draw(x + position.x, y + position.y, cam);
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
} // namespace funkin
