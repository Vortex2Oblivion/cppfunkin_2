#pragma once

#include <string>
#define LUA_VERSION_NUM 505
#include "funkin/Sprite.hpp"
#include "sol/sol.hpp"

namespace funkin::modding {
	class LuaScript {
	public:
		explicit LuaScript(const std::string &path);
		~LuaScript();

		[[nodiscard]] size_t getMemoryUsage() const;

		template<typename... Args>
		void call(const std::string &name, Args... args) {
			if (closed) {
				return;
			}
			if (sol::optional<sol::function> func = state[name]) {
				func->operator()(args...);
			}
		}

		template<typename T>
		void set(std::string name, T value) {
			if (closed) {
				return;
			}
			state[name] = value;
		}


		/**
		 * Convert a Lua sequence into a C++ vector
		 * Throw exception on errors or wrong types
		 * @see https://stackoverflow.com/questions/40755871/safely-pass-lua-sequences-to-c-using-sol2
		 */
		template<typename T>
		static std::vector<T> tableToVector(sol::table t) {
			std::size_t sz = t.size();
			std::vector<T> res(sz);
			for (int i = 1; i <= sz; i++) {
				res[i - 1] = t[i];
			}
			return res;
		}

		static size_t getTotalMemoryUsage();

	private:
		bool closed = true;
		sol::state state;
		static std::vector<LuaScript *> activeScripts;

		template<typename T = Sprite>
		sol::usertype<T> bindSpriteSubclass(sol::state *_state, std::string name) {
			static_assert(std::is_base_of_v<Sprite, T>, "T must inherit from Sprite");
			auto luaType = _state->new_usertype<T>(name);
			luaType.set("alive", &T::alive);
			luaType.set("ID", &T::ID);
			luaType.set("position", &T::position);
			luaType.set("camera", &T::camera);

			luaType.set("drawHitbox", &T::drawHitbox);
			luaType.set("flipX", &T::flipX);
			luaType.set("flipY", &T::flipY);
			luaType.set("visible", &T::visible);
			luaType.set("angle", &T::angle);
			luaType.set("alpha", &T::alpha);
			luaType.set("blend", &T::blend);
			luaType.set("color", &T::color);
			luaType.set("hitboxColor", &T::hitboxColor);
			luaType.set("origin", &T::origin);
			luaType.set("offset", &T::offset);
			luaType.set("scale", &T::scale);
			luaType.set("scrollFactor", &T::scrollFactor);
			luaType.set("source", &T::source);
			luaType.set("dest", &T::dest);
			luaType.set("hitbox", &T::hitbox);
			luaType.set("texture", &T::texture);
			luaType.set("shaders", &T::shaders);
			luaType.set("animation", &T::animation);
			luaType.set("antialiasing", sol::property(&T::getAntialiasing, &T::setAntialiasing));
			luaType.set("textureWrap", sol::property(&T::getTextureWrap, &T::setTextureWrap));

			luaType.set("loadTexture", &T::loadTexture);
			luaType.set("makeTexture", &T::makeTexture);
			luaType.set("isOnScreen", &T::isOnScreen);
			luaType.set("getMidpoint", &T::getMidpoint);
			luaType.set("getCurrentAnimation", &T::getCurrentAnimation);
			luaType.set("updateHitbox", &T::updateHitbox);
			luaType.set("centerOffsets", &T::centerOffsets);
			luaType.set("centerOrigin", &T::centerOrigin);
			luaType.set("screenCenter", &T::screenCenter);
			luaType.set("centerOn", &T::centerOn);
			luaType.set("draw", &T::draw);
			luaType.set("update", &T::update);

			return luaType;
		}
	};
} // namespace funkin::modding
