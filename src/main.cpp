#include "raylib.h"

#include "funkin/Game.hpp"

int main() {

	InitWindow(1280, 720, "Friday Night Funkin'");
	InitAudioDevice();

	Music inst = LoadMusicStream("assets/songs/titular/Inst.ogg");
	Music voicesOpponent = LoadMusicStream("assets/songs/titular/Voices-player.ogg");
	Music voicesPlayer = LoadMusicStream("assets/songs/titular/Voices-opponent.ogg");

	PlayMusicStream(inst);
	PlayMusicStream(voicesOpponent);
	PlayMusicStream(voicesPlayer);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		UpdateMusicStream(inst);
		UpdateMusicStream(voicesOpponent);
		UpdateMusicStream(voicesPlayer);
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}
