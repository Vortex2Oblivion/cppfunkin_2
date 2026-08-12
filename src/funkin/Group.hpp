#pragma once

#include <memory>
#include <type_traits>
#include <vector>
#include "Object.hpp"

#ifndef GROUP_IMPL
#define GROUP_IMPL(name, base)                                                                                                             \
	template<typename T>                                                                                                                   \
	concept Is##base = std::is_base_of_v<base, T>;                                                                                         \
	template<Is##base T = base>                                                                                                            \
	class name : public base {                                                                                                             \
	public:                                                                                                                                \
		explicit name(float x = 0.0f, float y = 0.0f);                                                                                     \
		~name() override;                                                                                                                  \
                                                                                                                                           \
		void add(std::shared_ptr<T> object);                                                                                               \
		void remove(std::shared_ptr<T> object);                                                                                            \
		void clear();                                                                                                                      \
                                                                                                                                           \
		std::size_t size();                                                                                                                \
                                                                                                                                           \
		void draw(float x, float y, const std::shared_ptr<Camera> &cam) override;                                                          \
                                                                                                                                           \
		void update(float delta) override;                                                                                                 \
                                                                                                                                           \
		std::vector<std::shared_ptr<T>> members = {};                                                                                      \
	};                                                                                                                                     \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	name<T>::name(const float x, const float y) : base(x, y) {}                                                                            \
                                                                                                                                           \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	name<T>::~name() {                                                                                                                     \
		if (!WindowShouldClose()) {                                                                                                        \
			members.clear();                                                                                                               \
		}                                                                                                                                  \
	}                                                                                                                                      \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	void name<T>::add(std::shared_ptr<T> object) {                                                                                         \
		members.push_back(object);                                                                                                         \
	}                                                                                                                                      \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	void name<T>::remove(std::shared_ptr<T> object) {                                                                                      \
		members.erase(std::ranges::find(members, object));                                                                                 \
	}                                                                                                                                      \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	void name<T>::clear() {                                                                                                                \
		members.clear();                                                                                                                   \
	}                                                                                                                                      \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	std::size_t name<T>::size() {                                                                                                          \
		return members.size();                                                                                                             \
	}                                                                                                                                      \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	void name<T>::draw(const float x, const float y, const std::shared_ptr<Camera> &cam) {                                                 \
		for (auto member: members) {                                                                                                       \
			if (member != nullptr) {                                                                                                       \
				member->draw(x + position.x, y + position.y, cam);                                                                         \
			}                                                                                                                              \
		}                                                                                                                                  \
	}                                                                                                                                      \
                                                                                                                                           \
	template<Is##base T>                                                                                                                   \
	void name<T>::update(float delta) {                                                                                                    \
		for (auto member: members) {                                                                                                       \
			if (member != nullptr) {                                                                                                       \
				member->update(delta);                                                                                                     \
			}                                                                                                                              \
		}                                                                                                                                  \
	}
#endif

namespace funkin {
	GROUP_IMPL(Group, Object)
} // namespace funkin
