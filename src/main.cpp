#include "PlayScene.hpp"
#include "raylib.h"

#include "funkin/Game.hpp"

using namespace funkin;
using namespace scenes;

int main() {

	InitWindow(1280, 720, "Friday Night Funkin'");
	InitAudioDevice();

	Game::start(PlayScene());

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
