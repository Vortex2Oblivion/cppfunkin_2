#include "Song.hpp"

#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"
#include "raylib.h"

using json = nlohmann::json;

namespace funkin::data {

	SongData Song::parseSong(const std::string &songName, const std::string& difficulty) {
		const std::string songPath = "assets/songs/" + songName + "/";
		if (FileExists((songPath + songName + "-metadata.json").c_str())) {
			return parseVSlice(songName, difficulty);
		}
		return parseLegacy(songName, difficulty);
	}

	SongData Song::parseLegacy(const std::string &songName, const std::string& difficulty) {
		const std::string path = "assets/songs/" + songName + "/" + songName + "-hard.json";
		auto chart = std::ifstream(path);
		auto parsedChart = json::parse(chart);
		chart.close();

		std::vector<NoteData> playerNotes = {};
		std::vector<NoteData> opponentNotes = {};

		nlohmann::json_abi_v3_12_0::json song;
		bool isPsychV1 = false;

		if (parsedChart["song"].contains("song")) {
			song = parsedChart["song"];
		} else {
			song = parsedChart;
			isPsychV1 = true;
		}

		for (auto sectionNotes : song["notes"]) {
			for (auto sectionNote : sectionNotes["sectionNotes"]) {
				if (isPsychV1) {
					if (!sectionNotes["mustHitSection"]) {
						if (sectionNote[1] > 3) {
							sectionNote[1] = static_cast<int>(sectionNote[1]) % 4;
						} else {
							sectionNote[1] = static_cast<int>(sectionNote[1]) + 4;
						}
					}
				}
				bool playerNote = sectionNote[1] < 4 ? static_cast<bool>(sectionNotes["mustHitSection"]) : !sectionNotes["mustHitSection"];
				std::uint8_t lane = static_cast<std::uint8_t>(sectionNote[1]) % 4 + (playerNote ? 0 : 4) % 4;
				try {
					auto noteData = NoteData{
						.time = static_cast<float>(sectionNote[0]),
						.lane = lane,
						.length = static_cast<float>(sectionNote[2]),
						.player = playerNote
					};
					if (playerNote) {
						playerNotes.push_back(noteData);
					} else {
						opponentNotes.push_back(noteData);
					}
				}
				catch (std::exception& e) {}
			}
		}

		return {
			.playerNotes = playerNotes,
			.opponentNotes = opponentNotes,
			.speed = song["speed"],
			.bpm = song["bpm"],
			.stage = song["stage"],
			.player = song["player1"],
			.opponent = song["player2"]
		};
	}

	SongData Song::parseVSlice(const std::string &songName, const std::string& difficulty) {
		const std::string path = "assets/songs/" + songName + "/" + songName;

		auto chart = std::ifstream(path + "-chart.json");
		auto meta = std::ifstream(path + "-metadata.json");

		auto parsedChart = json::parse(chart);
		auto parsedMeta = json::parse(meta);

		chart.close();
		meta.close();

		std::vector<NoteData> playerNotes = {};
		std::vector<NoteData> opponentNotes = {};

		std::vector<EventData> events = {};

		for (auto note: parsedChart["notes"][difficulty]) {
			bool player = note["d"] < 4;

			auto noteData = NoteData{
				.time = note["t"],
				.lane = static_cast<uint8_t>(static_cast<short>(note["d"]) % 4),
				.length = note.contains("l") ? static_cast<float>(note["l"]) : 0.0f,
				.player = player
			};

			if (player) {
				playerNotes.push_back(noteData);
			} else {
				opponentNotes.push_back(noteData);
			}
		}

		for (auto event : parsedChart["events"]) {
			events.push_back(EventData{
				.time = event["t"],
				.name = event["e"],
				.parameters = event["v"],
			});
			std::ranges::sort(events, [](const EventData& a, const EventData& b) {return a.time < b.time;});

		}

		return {
			.playerNotes = playerNotes,
			.opponentNotes = opponentNotes,
			.events = events,
			.speed = parsedChart["scrollSpeed"][difficulty],
			.bpm = parsedMeta["timeChanges"][0]["bpm"],
			.stage = parsedMeta["playData"]["stage"],
			.player = parsedMeta["playData"]["characters"]["player"],
			.opponent = parsedMeta["playData"]["characters"]["opponent"]
		};
	}
}