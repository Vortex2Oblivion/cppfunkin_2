#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

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
	} SongData;


	class Song {
	public:
		static SongData parseSong(const std::string &songName, const std::string &difficulty);
		static SongData parseVSlice(const std::string &songName, const std::string &difficulty);
		static SongData parseLegacy(const std::string &songName, const std::string &difficulty);
	};
} // namespace funkin::data
