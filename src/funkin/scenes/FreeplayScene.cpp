#include "FreeplayScene.hpp"

#include <fstream>
#include <iostream>

#include "PlayScene.hpp"
#include "MainMenuScene.hpp"
#include "funkin/Game.hpp"
#include "funkin/sound/SoundManager.hpp"
#include "funkin/Text.hpp"
#include "nlohmann/json.hpp"
#include "raylib.h"

#define _L TraceLog(3,TextFormat("%s", LINE++));

using json = nlohmann::json;

namespace funkin::scenes {
	FreeplayScene::FreeplayScene() = default;

	FreeplayScene::~FreeplayScene() { };

	void FreeplayScene::create() {
		FunkinScene::create();

		// std::array<std::string, 6> songList = {"blissful erect", "bonedoggle", "darnell bf mix", "b2llistic", "spine crusher", "thearchy"};



		menuBG = std::make_shared<Sprite>();
		menuBG->loadTexture("assets/images/menuDesat.png");
		menuBG->screenCenter();
		add(menuBG);

		songTexts = std::make_shared<Group<objects::Alphabet>>();
		add(songTexts);
		int i = 0;
		for (const auto &file: std::filesystem::directory_iterator("assets/songs/")) {
			auto fileString = file.path().filename();
			const auto song = std::make_shared<objects::Alphabet>(90, 320, fileString);
			song->isMenuItem = true;
			song->targetY = i;
			song->ID = i++;
			songTexts->add(song);
			difficulties.push_back({});
		}

		difficultyText = std::make_shared<Text>(0,0,"");
		difficultyText->borderSize=1;
		add(difficultyText);


		changeSelection(0);
		changeDifficulty(0);
	}

	void FreeplayScene::update(const float delta) {
		FunkinScene::update(delta);

		if (IsKeyPressed(KEY_DOWN)) {
			changeSelection(1);
		}
		else if (IsKeyPressed(KEY_UP)) {
			changeSelection(-1);
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			changeDifficulty(-1);
		}
		else if (IsKeyPressed(KEY_RIGHT)) {
			changeDifficulty(1);
		}
		else if (GetMouseWheelMove() != 0) {
			changeSelection(-static_cast<int>(GetMouseWheelMove()));
		}
		else if (IsKeyPressed(KEY_ENTER)) {
			Game::switchScene(std::make_unique<PlayScene>(songTexts->members[curSelected]->getText(),difficulties[curSelected][curDifficulty]));
		}else if (IsKeyPressed(KEY_BACKSPACE)) {
			Game::switchScene(std::make_unique<MainMenuScene>());
		}
	}

	void FreeplayScene::changeDifficulty(const int change) {
		const std::string songName = songTexts->members[curSelected]->getText();
		std::vector<std::string> &difficulty_list = difficulties.at(curSelected);
		if(difficulty_list.size()==0){
			const std::string path = "assets/songs/"+songName+"/";
			const std::string metadata_path = (path + songName+"-metadata.json");
			if(FileExists(metadata_path.c_str())){
				try{
					auto meta = std::ifstream(metadata_path);
					auto parsedMeta = json::parse(meta);
					meta.close();
					auto chart_difficulties = parsedMeta["playData"]["difficulties"];
					if(chart_difficulties.size() == 0){throw "Chart has invalid size!";}
					for (const std::string &difficulty: chart_difficulties ) {
						difficulty_list.push_back(difficulty);
					}
				}catch(...){
					difficulty_list.clear();
					TraceLog(5,"Unable to load metadata.");

				}
			}else{

				for (const auto &file: std::filesystem::directory_iterator(path)) {
					std::string filename = file.path().filename();
					if(!filename.ends_with(".json") || filename == "events.json") continue;
					difficulty_list.push_back(filename);
				}
			}
			if(difficulty_list.size() == 0){
				TraceLog(5,"Unable to get difficulties, using fallback!");
				difficulty_list.push_back("easy");
				difficulty_list.push_back("normal");
				difficulty_list.push_back("hard");
			}
		}

		curDifficulty = static_cast<int>(Wrap(static_cast<float>(curDifficulty + change), 0, static_cast<float>(difficulty_list.size())));
		if (change != 0){
			sound::SoundManager::playSound("assets/sounds/scrollMenu.ogg");
		}
		difficultyText->setText(difficulty_list.at(curDifficulty));
		difficultyText->screenCenter(math::Axes::X);

	}

	void FreeplayScene::changeSelection(const int change) {
		curSelected = static_cast<int>(Wrap(static_cast<float>(curSelected + change), 0, static_cast<float>(songTexts->size())));
		for (auto i = 0; i < songTexts->size(); i++) {
			songTexts->members[i]->targetY = i - curSelected;
		}
		if (change != 0) {
			changeDifficulty(0);
			sound::SoundManager::playSound("assets/sounds/scrollMenu.ogg");
		}
	}
} // namespace funkin::scenes
