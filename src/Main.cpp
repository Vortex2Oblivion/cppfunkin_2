#include "funkin/Game.hpp"
#include "funkin/scenes/MainMenuScene.hpp"
#include "funkin/scenes/PlayScene.hpp"
#include "raylib.h"

int main() {

	constexpr int windowWidth = 1280;
	constexpr int windowHeight = 720;
	constexpr auto windowTitle = "Friday Night Funkin'";

	InitWindow(windowWidth, windowHeight, windowTitle);
	InitAudioDevice();

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()) * 2);

	funkin::Game::start(std::make_unique<funkin::scenes::MainMenuScene>());

	while (!WindowShouldClose()) {
		funkin::Game::update(GetFrameTime());
	}

	funkin::Game::shutdown();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}
