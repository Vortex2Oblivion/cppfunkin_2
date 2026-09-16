#include "FreeplayScene.hpp"

#include <fstream>

#include "MainMenuScene.hpp"
#include "PlayScene.hpp"
#include "funkin/Game.hpp"
#include "funkin/Text.hpp"
#include "funkin/sound/SoundManager.hpp"
#include "funkin/ui/AlphabetList.hpp"
#include "nlohmann/json.hpp"
#include "raylib.h"

using json = nlohmann::json;

namespace funkin::scenes {
	FreeplayScene::FreeplayScene() = default;

	FreeplayScene::~FreeplayScene() = default;

	void FreeplayScene::create() {
		FunkinScene::create();

		script = std::make_unique<modding::LuaScript>("assets/data/freeplay.lua");

		menuBG = std::make_shared<Sprite>();
		menuBG->loadTexture("assets/images/menuDesat.png");
		menuBG->screenCenter();
		add(menuBG);

		songTexts = std::make_shared<AlphabetList>();
		add(songTexts);

		script->set("addSong", [this](const std::string &song, const std::string &icon, const sol::table &difficulties, const Color color) {
			std::unordered_map<std::string, std::filesystem::path> charts = {};
			std::unordered_map<std::string, std::filesystem::path> metas = {};


			const auto pathMeta = std::format("assets/songs/{}/{}-metadata.json", song, song);

			auto rawJson = LoadFileText(pathMeta.c_str());
			json metadata = json::parse(rawJson);
			UnloadFileText(rawJson);

			for (const auto &difficulty: metadata["playData"]["difficulties"]) {
				charts[difficulty] = std::format("assets/songs/{}/{}-chart.json", song, song);
				metas[difficulty] = pathMeta;
			}

			for (const auto &songVariation: metadata["playData"]["songVariations"]) {
				const auto variantPathMeta = std::format("assets/songs/{}/{}-metadata-{}.json", song, song, std::string(songVariation));

				auto rawJsonVariant = LoadFileText(variantPathMeta.c_str());
				json variantMetadata = json::parse(rawJsonVariant);
				UnloadFileText(rawJsonVariant);

				for (const auto &difficulty: variantMetadata["playData"]["difficulties"]) {
					if (charts.contains(difficulty)) {
						continue;
					}
					charts[difficulty] = std::format("assets/songs/{}/{}-chart-{}.json", song, song, std::string(songVariation));
					metas[difficulty] = variantPathMeta;
				}
			}

			songs.push_back(FreeplaySong{.name = song,
										 .icon = icon,
										 .difficulties = modding::LuaScript::tableToVector<std::string>(difficulties),
										 .color = color,
										 .charts = charts,
										 .metas = metas});

			const auto healthIcon = std::make_shared<objects::HealthIcon>(0, 0, icon);
			icons.push_back(healthIcon);
			add(healthIcon);

			songTexts->add(std::make_shared<objects::Alphabet>(90, 320, song));
		});

		script->call("onCreateSongs");

		difficultyText = std::make_shared<Text>(0, 0, "");
		difficultyText->loadFont("assets/fonts/vcr.ttf");
		difficultyText->borderSize = 2;
		difficultyText->size = 22.0f;
		add(difficultyText);

		songTexts->changeSelection(0);
	}

	void FreeplayScene::update(const float delta) {
		FunkinScene::update(delta);

		FreeplaySong currentSong = songs[songTexts->currentSelected];

		if (IsKeyPressed(KEY_ENTER)) {

			const std::string difficulty = currentSong.difficulties[currentDifficulty];

			PlayScene::songData = data::Song::parseVSlice(currentSong.charts[difficulty], currentSong.metas[difficulty], difficulty);
			PlayScene::songName = currentSong.name;

			Game::switchScene(std::make_unique<PlayScene>());
		} else if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE)) {
			Game::switchScene(std::make_unique<MainMenuScene>());
		} else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
			if (currentDifficulty == 0) {
				currentDifficulty = currentSong.difficulties.size() - 1;
			} else {
				currentDifficulty--;
			}
		} else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
			if (currentDifficulty == currentSong.difficulties.size() - 1) {
				currentDifficulty = 0;
			} else {
				currentDifficulty++;
			}
		} else {
			songTexts->checkInput();
		}

		if (currentDifficulty >= currentSong.difficulties.size()) {
			currentDifficulty = static_cast<int>(currentSong.difficulties.size() / 2);
		}

		difficultyText->setText(currentSong.difficulties[currentDifficulty]);
		difficultyText->screenCenter(math::Axes::X);

		for (size_t i = 0; i < songTexts->size(); i++) {
			icons[i]->position = songTexts->members[i]->position;

			auto [x, y] = songTexts->members[i]->getSize();

			icons[i]->position.x += x;
			icons[i]->centerOn(Rectangle{.x = 0.0f, .y = songTexts->members[i]->position.y, .width = 0.0f, .height = y}, math::Axes::Y);
		}
		menuBG->color = ColorLerp(menuBG->color, songs[songTexts->currentSelected].color, 0.045f * (delta / (1.0f / 60.0f)));
	}
} // namespace funkin::scenes
