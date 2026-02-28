#pragma once

#include <string>
#include "luaaa.hpp"

namespace funkin::modding {
    class LuaScript {
        public:
            LuaScript(const std::string& path);
            ~LuaScript();
        
        private:
            lua_State* state; 
        
    };
} // namespace funkin::modding
