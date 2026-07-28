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
set(RAYTWEEN_SRC "${RAYTWEEN_DIR}/raytween.cpp" "${RAYTWEEN_DIR}/tween.cpp")

include_directories(
        "src/"
        ${LUA_DIR}
        ${RAYTWEEN_DIR}
)

add_executable(${PROJECT_NAME} src/Main.cpp ${SRC} ${LUA_SRC} ${RAYTWEEN_SRC})

if(WIN32)
       if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc -static")
        endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif(WIN32)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

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
