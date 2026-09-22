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
			return parseVSlice(songPath + songName + "-chart.json", songPath + songName + "-metadata.json", difficulty);
		}
		return parseLegacy(songPath + songName + "-" + difficulty + ".json");
	}

	SongData Song::parseLegacy(const std::filesystem::path &path) {
		auto chart = LoadFileText(path.string().c_str());
		auto parsedChart = json::parse(chart);
		UnloadFileText(chart);

		std::vector<NoteData> playerNotes = {};
		std::vector<NoteData> opponentNotes = {};
		std::vector<EventData> events = {};

		json song;
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
				}
				if (sectionNote[1] == -1) { // old psych event note
					nlohmann::json parameters;
					parameters["value1"] = sectionNote[3];
					parameters["value2"] = sectionNote[4];
					events.push_back(EventData{.time = sectionNote[0], .name = sectionNote[2], .parameters = parameters});
					continue;
				}

				bool playerNote = sectionNote[1] < 4 ? static_cast<bool>(sectionNotes["mustHitSection"]) : !sectionNotes["mustHitSection"];
				std::uint8_t lane = static_cast<std::uint8_t>(sectionNote[1]) % 4 + (playerNote ? 0 : 4) % 4;
				try {
					if (sectionNote[2].is_string()) {
						continue; // what
					}
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
		if (FileExists((path.string() + "/events.json").c_str())) {
			auto eventStream = std::ifstream(path.string() + "/events.json");
			auto parsedEvents = json::parse(eventStream);
			eventStream.close();

			if (parsedEvents["song"].contains("events")) {
				for (auto eventsAtTime: parsedEvents["song"]["events"]) {
					float time = eventsAtTime[0];
					for (auto event: eventsAtTime[1]) {
						json parameters;
						parameters["value1"] = event[1];
						parameters["value2"] = event[2];
						events.push_back(EventData{.time = time, .name = event[0], .parameters = parameters});
					}
				}
			} else { // old psych events format
				for (const auto &eventNotes: parsedEvents["song"]["notes"]) {
					for (auto event: eventNotes["sectionNotes"]) {
						if (event[1] == -1) {
							json parameters;
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
		} else {
			spectator = "";
		}

		std::string stage = song.contains("stage") ? song["stage"] : "";

		return {.playerNotes = playerNotes,
				.opponentNotes = opponentNotes,
				.events = events,
				.speed = song["speed"],
				.bpm = song["bpm"],
				.stage = stage,
				.player = song["player1"],
				.opponent = song["player2"],
				.spectator = spectator,
				.name = song["song"],
				.instrumental = ""};
	}

	SongData Song::parseVSlice(const std::filesystem::path &chartPath, const std::filesystem::path &metaPath,
							   const std::string &difficulty) {
		auto chart = LoadFileText(chartPath.string().c_str());
		auto meta = LoadFileText(metaPath.string().c_str());

		auto parsedChart = json::parse(chart);
		auto parsedMeta = json::parse(meta);

		UnloadFileText(chart);
		UnloadFileText(meta);

		std::vector<NoteData> playerNotes = {};
		std::vector<NoteData> opponentNotes = {};

		std::vector<EventData> events = {};

		for (auto note: parsedChart["notes"][difficulty]) {
			const bool player = note["d"] < 4;

			auto noteData = NoteData{.player = player,
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
		}

		std::ranges::sort(events, [](const EventData &a, const EventData &b) { return a.time < b.time; });

		const std::string instrumental =
				parsedMeta["playData"]["characters"].contains("instrumental") ? parsedMeta["playData"]["characters"]["instrumental"] : "";

		return {.playerNotes = playerNotes,
				.opponentNotes = opponentNotes,
				.events = events,
				.speed = parsedChart["scrollSpeed"][difficulty],
				.bpm = parsedMeta["timeChanges"][0]["bpm"],
				.stage = parsedMeta["playData"]["stage"],
				.player = parsedMeta["playData"]["characters"]["player"],
				.opponent = parsedMeta["playData"]["characters"]["opponent"],
				.spectator = parsedMeta["playData"]["characters"]["girlfriend"],
				.name = parsedMeta["songName"],
				.instrumental = instrumental};
	}

	static std::string getSongsPath(std::string_view songName) { return std::format("assets/songs/{}/", songName); }

	Music Song::getInst(const std::string &songName, const std::string &variant) {
		Music inst = {};

		const std::string songsPath = getSongsPath(songName);

		if (FileExists(TextFormat("%sInst-%s.ogg", songsPath.c_str(), variant.c_str()))) {
			inst = LoadMusicStream(TextFormat("%sInst-%s.ogg", songsPath.c_str(), variant.c_str()));
		} else if (FileExists(TextFormat("%sInst.ogg", songsPath.c_str()))) {
			inst = LoadMusicStream(TextFormat("%sInst.ogg", songsPath.c_str()));
		}

		return inst;
	}


	Music Song::getPlayerVoices(const std::string &songName, const std::string &player, const std::string &variant) {
		Music playerVoices = {};

		std::string songsPath = getSongsPath(songName);

		const auto voicesCharPath = std::format("{}Voices-{}.ogg", songsPath, player);
		const auto voicesPlayerPath = std::format("{}Voices-player.ogg", songsPath);
		const auto voicesPath = std::format("{}Voices.ogg", songsPath);

		const auto voicesCharPathVariant = std::format("{}Voices-{}-{}.ogg", songsPath, player, variant);
		const auto voicesPlayerPathVariant = std::format("{}Voices-player-{}.ogg", songsPath, variant);
		const auto voicesPathVariant = std::format("{}Voices-{}.ogg", songsPath, variant);

		if (FileExists(voicesCharPathVariant.c_str())) {
			playerVoices = LoadMusicStream(voicesCharPathVariant.c_str());
		} else if (FileExists(voicesPlayerPathVariant.c_str())) {
			playerVoices = LoadMusicStream(voicesPlayerPathVariant.c_str());
		} else if (FileExists(voicesCharPath.c_str())) {
			playerVoices = LoadMusicStream(voicesCharPath.c_str());
		} else if (FileExists(voicesPlayerPath.c_str())) {
			playerVoices = LoadMusicStream(voicesPlayerPath.c_str());
		}


		if (!IsMusicValid(playerVoices)) {
			if (FileExists(voicesPathVariant.c_str())) {
				playerVoices = LoadMusicStream(voicesPathVariant.c_str());
			} else if (FileExists(voicesPath.c_str())) {
				playerVoices = LoadMusicStream(voicesPath.c_str());
			}
		}

		return playerVoices;
	}

	Music Song::getOpponentVoices(const std::string &songName, const std::string &player, const std::string &variant) {
		Music opponentVoices = {};

		std::string songsPath = getSongsPath(songName);

		const auto voicesCharPath = std::format("{}Voices-{}.ogg", songsPath, player);
		const auto voicesOpponentPath = std::format("{}Voices-opponent.ogg", songsPath);

		const auto voicesCharPathVariant = std::format("{}Voices-{}-{}.ogg", songsPath, player, variant);
		const auto voicesOpponentPathVariant = std::format("{}Voices-opponent-{}.ogg", songsPath, variant);

		if (FileExists(voicesCharPathVariant.c_str())) {
			opponentVoices = LoadMusicStream(voicesCharPathVariant.c_str());
		} else if (FileExists(voicesOpponentPathVariant.c_str())) {
			opponentVoices = LoadMusicStream(voicesOpponentPathVariant.c_str());
		} else if (FileExists(voicesCharPath.c_str())) {
			opponentVoices = LoadMusicStream(voicesCharPath.c_str());
		} else if (FileExists(voicesOpponentPath.c_str())) {
			opponentVoices = LoadMusicStream(voicesOpponentPath.c_str());
		}

		return opponentVoices;
	}
} // namespace funkin::data
