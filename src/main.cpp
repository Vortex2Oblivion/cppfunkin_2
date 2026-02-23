#include "PlayScene.hpp"
#include "raylib.h"

#include "funkin/Game.hpp"

int main() {
	InitWindow(1280, 720, "Friday Night Funkin'");
	InitAudioDevice();

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()) * 2);

	funkin::Game::start(std::make_unique<funkin::scenes::PlayScene>());

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		funkin::Game::update(GetFrameTime());
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}