#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace funkin::data {
	typedef struct NoteData {
		float time;
		uint8_t lane;
		float length;
		bool player;
	}NoteData;

	typedef struct SongData {
		std::vector<NoteData> notes;
		float speed;
		float bpm;
	}SongData;

	class Song {
		public:
			static SongData parseSong(const std::string& songName);
	};

}
