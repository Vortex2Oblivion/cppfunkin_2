#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"
#include "raylib.h"

namespace funkin::data {
	typedef struct NoteData {
		bool player;
		uint8_t lane;
		float time;
		float length;
	} NoteData;

	typedef struct EventData {
		float time;
		std::string name;
		nlohmann::basic_json<> parameters;
	} EventData;

	typedef struct SongData {
		std::vector<NoteData> playerNotes;
		std::vector<NoteData> opponentNotes;
		std::vector<EventData> events;
		float speed;
		float bpm;
		std::string stage;
		std::string player;
		std::string opponent;
		std::string spectator;
		std::string path;
		std::string name;
		std::string instrumental;
	} SongData;


	class Song {
	public:
		static SongData parseSong(const std::string &songName, const std::string &difficulty);
		static SongData parseVSlice(const std::filesystem::path &chartPath, const std::filesystem::path &metaPath,
									const std::string &difficulty);
		static SongData parseLegacy(const std::filesystem::path &path);

		static Music getInst(const std::string &songName, const std::string &variant);
		static Music getPlayerVoices(const std::string &songName, const std::string &player, const std::string &variant = "");
		static Music getOpponentVoices(const std::string &songName, const std::string &player, const std::string &variant = "");
	};
} // namespace funkin::data
