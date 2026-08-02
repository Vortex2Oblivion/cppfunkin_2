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

		void add(T *object);
		void add(std::shared_ptr<T> object);
		void remove(std::shared_ptr<T> object);

		std::size_t size();

		void draw(float x, float y, const std::shared_ptr<Camera> &cam) override;

		void update(float delta) override;

		std::vector<std::shared_ptr<T>> members = {};
	};

	template<IsObject T>
	Group<T>::Group(const float X, const float Y) : Object(X, Y) {
		alive = true;
	}

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
	void Group<T>::add(T *object) {
		add(std::shared_ptr<Object>(object));
	}

	template<IsObject T>
	void Group<T>::remove(std::shared_ptr<T> object) {
		members.erase(std::ranges::find(members, object));
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
