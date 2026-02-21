#include "PlayScene.hpp"

#include "NoteLane.hpp"
#include "PlayField.hpp"
#include "Sprite.hpp"

namespace funkin::scenes {
	PlayScene::PlayScene() = default;
	PlayScene::~PlayScene() = default;

	void PlayScene::create() {
		Scene::create();

		const std::string songName = "titular";

		inst = LoadMusicStream(("assets/songs/"+songName+"/Inst.ogg").c_str());
		voices = LoadMusicStream(("assets/songs/"+songName+"/Voices-opponent.ogg").c_str());
		voicesPlayer = LoadMusicStream(("assets/songs/"+songName+"/Voices-player.ogg").c_str());

		std::vector<Music> tracks = {inst, voices, voicesPlayer};

		conductor = std::make_shared<Conductor>(tracks);
		conductor->bpm = 110.0f;
		conductor->start();

		auto song = data::Song::parseSong(songName);

		const auto opponentField = std::make_shared<PlayField>(100.0f, 100.0f, 4, song.speed, song.opponentNotes, conductor);
		add(opponentField);

		const auto playerField = std::make_shared<PlayField>(static_cast<float>(GetRenderWidth()) / 2 + 100.0f, 100.0f, 4, song.speed, song.playerNotes, conductor);
		add(playerField);
	}

	void PlayScene::update(const float delta) {
		Scene::update(delta);
		conductor->update(delta);
	}
}
