cmake_minimum_required(VERSION 4.1)
project(cppfunkin_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "cmake-build-release")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "cmake-build-debug")
endif()

include_directories(
        "src/funkin"
        "src/funkin/game"
        "src/funkin/scenes"
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
        src/funkin/game/NoteLane.cpp
        src/funkin/game/NoteLane.hpp
        src/funkin/game/Conductor.cpp
        src/funkin/game/Conductor.hpp
        src/funkin/game/Note.cpp
        src/funkin/game/Note.hpp
        src/funkin/game/StrumNote.cpp
        src/funkin/game/StrumNote.hpp
        src/funkin/data/Song.cpp
        src/funkin/data/Song.hpp
        src/funkin/game/PlayField.cpp
        src/funkin/game/PlayField.hpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(external/raylib)
target_link_libraries(${PROJECT_NAME} raylib)

add_subdirectory(external/json)
target_link_libraries(${PROJECT_NAME} nlohmann_json)

add_dependencies(${PROJECT_NAME} copy_assets)

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
        COMMENT "COPYING ASSETS"
)