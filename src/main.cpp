#include "PlayScene.hpp"
#include "raylib.h"

#include "funkin/Game.hpp"
#include "luaaa.hpp"
#include <iostream>

int main()
{

    lua_State *L = luaL_newstate();  // Create a new Lua state
    luaL_openlibs(L);                 // Load Lua libraries
    luaL_dostring(L, "print('Hi from lua!')"); // Execute Lua script
    lua_close(L);                     // Close the Lua state
	
	InitWindow(1280, 720, "Friday Night Funkin'");
	InitAudioDevice();

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()) * 2);


	funkin::Game::start(std::make_unique<funkin::scenes::PlayScene>());

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		funkin::Game::update(GetFrameTime());
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}