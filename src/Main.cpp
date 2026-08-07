#include "funkin/Game.hpp"
#include "funkin/scenes/PlayScene.hpp"
#include "funkin/scenes/TitleScene.hpp"
#include "raylib.h"

#ifdef _WIN32
#include "external/fix_win32_compatibility.h"
#include "dwmapi.h"
#endif

int main() {

	constexpr int windowWidth = 1280;
	constexpr int windowHeight = 720;
	constexpr auto windowTitle = "Friday Night Funkin'";

	InitWindow(windowWidth, windowHeight, windowTitle);

#ifdef _WIN32
	constexpr int darkMode = 1;

	const auto window = static_cast<HWND>(GetWindowHandle());
	// ReSharper disable once CppFunctionResultShouldBeUsed
	DwmSetWindowAttribute(window, 20, &darkMode, sizeof(darkMode));
	UpdateWindow(window);
#endif

	InitAudioDevice();

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()) * 2);

	funkin::Game::start(std::make_unique<funkin::scenes::TitleScene>());

	while (!WindowShouldClose()) {
		funkin::Game::update(GetFrameTime());
	}

	funkin::Game::shutdown();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}
