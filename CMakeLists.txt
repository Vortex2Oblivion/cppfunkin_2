cmake_minimum_required(VERSION 4.1)
project(cppfunkin_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

include_directories(
        "src/funkin"
        "src/funkin/data"
        "src/funkin/game"
        "src/funkin/objects"
        "src/funkin/scenes"
        "external/lua"
)

add_executable(${PROJECT_NAME} src/main.cpp
        src/funkin/Group.hpp
        src/funkin/Object.hpp
        src/funkin/Object.cpp
        src/funkin/Game.cpp
        src/funkin/Game.hpp
        src/funkin/Scene.cpp
        src/funkin/Scene.hpp
        src/funkin/scenes/PlayScene.cpp
        src/funkin/scenes/PlayScene.hpp
        src/funkin/Sprite.cpp
        src/funkin/Sprite.hpp
        src/funkin/objects/notes/NoteLane.cpp
        src/funkin/objects/notes/NoteLane.hpp
        src/funkin/game/Conductor.cpp
        src/funkin/game/Conductor.hpp
        src/funkin/objects/notes/Note.cpp
        src/funkin/objects/notes/Note.hpp
        src/funkin/objects/notes/StrumNote.cpp
        src/funkin/objects/notes/StrumNote.hpp
        src/funkin/data/Song.cpp
        src/funkin/data/Song.hpp
        src/funkin/objects/notes/PlayField.cpp
        src/funkin/objects/notes/PlayField.hpp
        src/funkin/data/animation/Animation.hpp
        src/funkin/game/AnimationController.cpp
        src/funkin/game/AnimationController.hpp
        src/funkin/data/animation/Frame.hpp
        src/funkin/data/animation/Animation.cpp

        external/lua/lapi.c
        external/lua/lauxlib.c
        external/lua/lbaselib.c
        external/lua/lcode.c
        external/lua/lcorolib.c
        external/lua/lctype.c
        external/lua/ldblib.c
        external/lua/ldebug.c
        external/lua/ldo.c
        external/lua/ldump.c
        external/lua/lfunc.c
        external/lua/lgc.c
        external/lua/linit.c
        external/lua/liolib.c
        external/lua/llex.c
        external/lua/lmathlib.c
        external/lua/lmem.c
        external/lua/loadlib.c
        external/lua/lobject.c
        external/lua/lopcodes.c
        external/lua/loslib.c
        external/lua/lparser.c
        external/lua/lstate.c
        external/lua/lstring.c
        external/lua/lstrlib.c
        external/lua/ltable.c
        external/lua/ltablib.c
        external/lua/ltm.c
        external/lua/lundump.c
        external/lua/lutf8lib.c
        external/lua/lvm.c
        external/lua/lzio.c
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(external/raylib)
target_link_libraries(${PROJECT_NAME} raylib)

add_subdirectory(external/json)
target_link_libraries(${PROJECT_NAME} nlohmann_json)

add_subdirectory(external/pugixml)
target_link_libraries(${PROJECT_NAME} pugixml)

include_directories(external/luaaa)

add_dependencies(${PROJECT_NAME} copy_assets)

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
        COMMENT "COPYING ASSETS"
)