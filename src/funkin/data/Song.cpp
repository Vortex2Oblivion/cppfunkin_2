#include "Song.hpp"

#include <fstream>
#include <iostream>

#include "funkin/game/events/CameraTarget.hpp"
#include "nlohmann/json.hpp"
#include "raylib.h"

using json = nlohmann::json;

namespace funkin::data {
	SongData Song::parseSong(const std::string &songName, const std::string &difficulty) {
		const std::string songPath = "assets/songs/" + songName + "/";
		if (FileExists((songPath + difficulty).c_str())) {
			return parseLegacy(songPath + difficulty);
		}
		if (FileExists((songPath + songName + "-metadata.json").c_str())) {
			return parseVSlice(songPath + songName, difficulty);
		}
		return parseLegacy(songPath + songName + "-" + difficulty + ".json");
	}
	SongData Song::parseSongFromPath(const std::string &path, const std::string &difficulty) {
		if (FileExists((path + "-metadata.json").c_str())) {
			return parseVSlice(path, difficulty);
		}
		if (FileExists((path + ".json").c_str())) {
			return parseLegacy(path+".json");
		}
		return parseLegacy(path);
	}
	SongData Song::parseLegacy(const std::string &path) {
		auto chart = std::ifstream(path);
		auto parsedChart = json::parse(chart);
		chart.close();


		std::vector<NoteData> playerNotes = {};
		std::vector<NoteData> opponentNotes = {};
		std::vector<EventData> events = {};

		nlohmann::json_abi_v3_12_0::json song;
		bool isPsychV1 = false;

		if (parsedChart["song"].contains("song")) {
			song = parsedChart["song"];
		} else {
			song = parsedChart;
			isPsychV1 = true;
		}

		std::int8_t lastMustHit = -1;
		std::uint16_t section = 0;

		for (auto sectionNotes: song["notes"]) {
			if (lastMustHit != static_cast<std::int8_t>(sectionNotes["mustHitSection"])) {
				lastMustHit = static_cast<std::int8_t>(sectionNotes["mustHitSection"]);


				nlohmann::basic_json time = 1000.f * static_cast<float>(section) * ((60.0f / static_cast<float>(song["bpm"])) / 4.0f) *
											(sectionNotes.contains("lengthInSteps") ? static_cast<float>(sectionNotes["lengthInSteps"])
																					: static_cast<float>(sectionNotes["sectionBeats"]) * 4);
				nlohmann::json parameters;
				parameters["char"] = (lastMustHit == 0 ? game::events::CameraTarget::DAD : game::events::CameraTarget::BOYFRIEND);

				events.push_back(EventData{.time = time, .name = "FocusCamera", .parameters = parameters});
			}
			for (auto sectionNote: sectionNotes["sectionNotes"]) {
				if (isPsychV1) {
					if (!sectionNotes["mustHitSection"]) {
						if (sectionNote[1] > 3) {
							sectionNote[1] = static_cast<int>(sectionNote[1]) % 4;
						} else {
							sectionNote[1] = static_cast<int>(sectionNote[1]) + 4;
						}
					}
				} else if (sectionNote[1] == -1) { // old psych event note
					nlohmann::json parameters;
					parameters["value1"] = sectionNote[3];
					parameters["value2"] = sectionNote[4];
					events.push_back(EventData{.time = sectionNote[0], .name = sectionNote[2], .parameters = parameters});
					continue;
				}

				bool playerNote = sectionNote[1] < 4 ? static_cast<bool>(sectionNotes["mustHitSection"]) : !sectionNotes["mustHitSection"];
				std::uint8_t lane = static_cast<std::uint8_t>(sectionNote[1]) % 4 + (playerNote ? 0 : 4) % 4;
				try {
					auto noteData = NoteData{.player = playerNote,
											 .lane = lane,
											 .time = static_cast<float>(sectionNote[0]),
											 .length = static_cast<float>(sectionNote[2])};
					if (playerNote) {
						playerNotes.push_back(noteData);
					} else {
						opponentNotes.push_back(noteData);
					}
				} catch ([[maybe_unused]] json::parse_error &e) {
					std::cerr << e.what() << std::endl;
				}
			}
			section++;
		}

		// load events from json
		if (FileExists((path + "/events.json").c_str())) {
			auto eventStream = std::ifstream(path + "/events.json");
			auto parsedEvents = json::parse(eventStream);
			eventStream.close();

			if (parsedEvents["song"].contains("events")) {
				for (auto eventsAtTime: parsedEvents["song"]["events"]) {
					float time = eventsAtTime[0];
					for (auto event: eventsAtTime[1]) {
						nlohmann::json parameters;
						parameters["value1"] = event[1];
						parameters["value2"] = event[2];
						events.push_back(EventData{.time = time, .name = event[0], .parameters = parameters});
					}
				}
			} else { // old psych events format
				for (const auto &eventNotes: parsedEvents["song"]["notes"]) {
					for (auto event: eventNotes["sectionNotes"]) {
						if (event[1] == -1) {
							nlohmann::json parameters;
							parameters["value1"] = event[3];
							parameters["value2"] = event[4];
							events.push_back(EventData{.time = event[0], .name = event[2], .parameters = parameters});
						}
					}
				}
			}
		}

		std::string spectator;

		if (song.contains("player3") && song["player3"] != "null" && !song["player3"].empty()) {
			spectator = song["player3"];
		} else if (song.contains("gf") && song["gf"] != "null" && !song["gf"].empty()) {
			spectator = song["gf"];
		} else if (song.contains("gfVersion") && song["gfVersion"] != "null" && !song["gfVersion"].empty()) {
			spectator = song["gfVersion"];
		}

		return {.playerNotes = playerNotes,
				.opponentNotes = opponentNotes,
				.events = events,
				.speed = song["speed"],
				.bpm = song["bpm"],
				.stage = song["stage"],
				.player = song["player1"],
				.opponent = song["player2"],
				.spectator = spectator};
	}

	SongData Song::parseVSlice(const std::string &path, const std::string &difficulty) {
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

			NoteData noteData = NoteData{.player = player,
									 .lane = static_cast<uint8_t>(static_cast<short>(note["d"]) % 4),
									 .time = note["t"],
									 .length = note.contains("l") ? static_cast<float>(note["l"]) : 0.0f};

			if (player) {
				playerNotes.push_back(noteData);
			} else {
				opponentNotes.push_back(noteData);
			}
		}

		for (auto event: parsedChart["events"]) {
			events.push_back(EventData{
					.time = event["t"],
					.name = event["e"],
					.parameters = event["v"],
			});
			std::ranges::sort(events, [](const EventData &a, const EventData &b) { return a.time < b.time; });
		}

		return {.playerNotes = playerNotes,
				.opponentNotes = opponentNotes,
				.events = events,
				.speed = parsedChart["scrollSpeed"][difficulty],
				.bpm = parsedMeta["timeChanges"][0]["bpm"],
				.stage = parsedMeta["playData"]["stage"],
				.player = parsedMeta["playData"]["characters"]["player"],
				.opponent = parsedMeta["playData"]["characters"]["opponent"],
				.spectator = parsedMeta["playData"]["characters"]["girlfriend"]};
	}
} // namespace funkin::data
