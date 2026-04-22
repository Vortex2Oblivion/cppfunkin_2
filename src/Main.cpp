#include "PlayScene.hpp"
#include "Game.hpp"
#include "raylib.h"

int main()
{

	constexpr int windowWidth = 1280;
	constexpr int windowHeight = 720;
	const auto windowTitle = "Friday Night Funkin'";

	InitWindow(windowWidth, windowHeight, windowTitle);
	InitAudioDevice();

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()) * 2);

	funkin::Game::start(std::make_unique<funkin::scenes::PlayScene>());

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		funkin::Game::update(GetFrameTime());
		EndDrawing();
	}


	CloseAudioDevice();
	CloseWindow();

	return 0;
}