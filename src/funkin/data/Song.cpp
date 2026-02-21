#include "Song.hpp"

#include <fstream>
#include  "nlohmann/json.hpp"

using json = nlohmann::json;

namespace funkin::data {
	SongData Song::parseSong(const std::string& songName) {
		const std::string path = "assets/songs/" + songName + "/" + songName;

		auto chart = std::ifstream(path + "-chart.json");
		auto meta = std::ifstream(path + "-metadata.json");

		auto parsedChart = json::parse(chart);
		auto parsedMeta = json::parse(meta);

		chart.close();
		meta.close();

		std::vector<NoteData> notes = {};

		for (auto note : parsedChart["notes"]["hard"]) {
			notes.push_back(NoteData{
				.time = note["t"],
				.lane = static_cast<uint8_t>(static_cast<short>(note["d"]) % 4),
				.length = note.contains("l") ? static_cast<float>(note["l"]) : 0.0f,
				.player = note["d"] < 4
			});
		}

		return {
			.notes = notes,
			.speed = parsedChart["scrollSpeed"]["hard"],
			.bpm = parsedMeta["timeChanges"][0]["bpm"]
		};
	}
}
