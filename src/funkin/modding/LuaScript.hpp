#pragma once

#include <string>
#define LUA_VERSION_NUM 505
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
	};
} // namespace funkin::modding
