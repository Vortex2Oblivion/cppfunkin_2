#include "PlayScene.hpp"
#include "raylib.h"

#include "funkin/Game.hpp"

using namespace funkin;
using namespace scenes;

int main() {

	InitWindow(1280, 720, "Friday Night Funkin'");
	InitAudioDevice();

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()) * 2);

	Game::start(std::make_unique<PlayScene>());

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		Game::update(GetFrameTime());
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}
