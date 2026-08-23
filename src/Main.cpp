#include "funkin/Game.hpp"
#include "funkin/scenes/PlayScene.hpp"
#include "funkin/scenes/TitleScene.hpp"

#ifdef _WIN32
#include "dwmapi.h"
#include "external/fix_win32_compatibility.h"
#elif __linux__
#include "gamemode_client.h"
#endif

#include "raylib.h"

int main() {

#if __linux__
	if (gamemode_request_start()) {
		std::cerr << "Failed to request gamemode start: " << gamemode_error_string() << std::endl;
	}
#endif

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
	SetExitKey(KEY_NULL);

	funkin::Game::start(std::make_unique<funkin::scenes::TitleScene>());

	while (!WindowShouldClose()) {
		funkin::Game::update(GetFrameTime());
	}

	funkin::Game::shutdown();

	CloseAudioDevice();
	CloseWindow();


#if __linux__
	if (gamemode_request_end()) {
		std::cerr << "Failed to request gamemode end: " << gamemode_error_string() << std::endl;
	}
#endif

	return 0;
}
