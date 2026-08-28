cmake_minimum_required(VERSION 4.1)
project(cppfunkin_2)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH "bin")

file(GLOB_RECURSE SRC "src/*.cpp")

set(LUA_DIR "external/lua")
file(GLOB LUA_SRC "${LUA_DIR}/*.c")
list(REMOVE_ITEM LUA_SRC "${PROJECT_SOURCE_DIR}/${LUA_DIR}/lua.c")
list(REMOVE_ITEM LUA_SRC "${PROJECT_SOURCE_DIR}/${LUA_DIR}/onelua.c")

set(RAYTWEEN_DIR "external/raytween/raylib tweening engine")
set(RAYTWEEN_SRC "${RAYTWEEN_DIR}/raytween.cpp" "${RAYTWEEN_DIR}/tween.cpp"
        src/funkin/group/SpriteGroup.hpp)

include_directories(
        "src/"
        ${LUA_DIR}
        ${RAYTWEEN_DIR}
)

if (UNIX AND NOT APPLE)
    include_directories(external/gamemode/lib)
endif ()


add_executable(${PROJECT_NAME} src/Main.cpp ${SRC} ${LUA_SRC} ${RAYTWEEN_SRC})

if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND UNIX)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexperimental-library")
endif ()

if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
    elseif (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    endif ()
    target_link_libraries(${PROJECT_NAME} dwmapi)
endif (WIN32)

#set(PLATFORM "SDL" CACHE STRING "" FORCE)

add_compile_definitions(SUPPORT_BUSY_WAIT_LOOP)
add_subdirectory(external/raylib)
target_link_libraries(${PROJECT_NAME} raylib)

add_subdirectory(external/json)
target_link_libraries(${PROJECT_NAME} nlohmann_json)

add_subdirectory(external/pugixml)
target_link_libraries(${PROJECT_NAME} pugixml)

add_subdirectory(external/eventpp)
target_link_libraries(${PROJECT_NAME} eventpp)

add_subdirectory(external/sol2)
target_link_libraries(${PROJECT_NAME} sol2)

add_dependencies(${PROJECT_NAME} copy_assets)

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${EXECUTABLE_OUTPUT_PATH}/assets

        COMMENT "COPYING ASSETS"
)

if (UNIX AND NOT APPLE)
    add_dependencies(${PROJECT_NAME} copy_gamemode_ini)
    add_custom_target(copy_gamemode_ini ALL
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/gamemode.ini
            ${EXECUTABLE_OUTPUT_PATH}/gamemode.ini

            COMMENT "COPYING TARGET SPECIFIC ASSETS"
    )
endif ()