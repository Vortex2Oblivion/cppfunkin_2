#include <iostream>


#include "funkin/Game.hpp"
#include "funkin/scenes/PlayScene.hpp"
#include "funkin/scenes/TitleScene.hpp"
#include "funkin/utilities/Save.hpp"
#include "rlgl.h"

#ifdef _WIN32
#include "external/fix_win32_compatibility.h"
#include "dwmapi.h"
#elif __linux__
#include "gamemode_client.h"
#endif

#include "raylib.h"

int main() {

	new funkin::utilities::Save("poop");

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

#ifdef false
	// https://stackoverflow.com/a/77160530
	rlSetBlendFactorsSeparate(RL_SRC_ALPHA, RL_ONE_MINUS_SRC_ALPHA, RL_ONE, RL_ONE_MINUS_SRC_ALPHA, RL_FUNC_ADD, RL_FUNC_ADD);
#else
	// https://github.com/raysan5/raylib/issues/3820#issuecomment-1962858674
	rlSetBlendFactorsSeparate(RL_SRC_ALPHA, RL_ONE_MINUS_SRC_ALPHA, RL_ONE, RL_ONE, RL_FUNC_ADD, RL_MAX);
#endif

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
