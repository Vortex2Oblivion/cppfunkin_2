#include "FreeplayScene.hpp"

#include "PlayScene.hpp"
#include "MainMenuScene.hpp"
#include "funkin/Game.hpp"
#include "funkin/sound/SoundManager.hpp"
#include "Text.hpp"

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

		difficultyText = std::make_shared<Group<Text>>();
		add(songTexts);
		songTexts = std::make_shared<Group<objects::Alphabet>>();
		add(songTexts);
		int i = 0;
		for (const auto &file: std::filesystem::directory_iterator("assets/songs/")) {
			auto fileString = file.path().filename();
			const auto song = std::make_shared<objects::Alphabet>(90, 320, fileString);
			song->isMenuItem = true;
			song->targetY = i;
			song->ID = i;
			songTexts->add(song);
		}
		// for (auto i = 0; i < songList.size(); i++) {
		// 	const auto song = std::make_shared<objects::Alphabet>(90, 320, songList[i]);
		// 	song->isMenuItem = true;
		// 	song->targetY = i;
		// 	song->ID = i;
		// 	songTexts->add(song);
		// }

		changeSelection(0);
	}

	void FreeplayScene::update(const float delta) {
		FunkinScene::update(delta);

		if (IsKeyPressed(KEY_DOWN)) {
			changeSelection(1);
		}
		else if (IsKeyPressed(KEY_UP)) {
			changeSelection(-1);
		}
		else if (GetMouseWheelMove() != 0) {
			changeSelection(-static_cast<int>(GetMouseWheelMove()));
		}
		else if (IsKeyPressed(KEY_ENTER)) {
			Game::switchScene(std::make_unique<PlayScene>(songTexts->members[curSelected]->getText()));
		}else if (IsKeyPressed(KEY_BACKSPACE)) {
			Game::switchScene(std::make_unique<MainMenuScene>());
		}
	}

	void FreeplayScene::changeSelection(const int change) {
		curSelected = static_cast<int>(Wrap(static_cast<float>(curSelected + change), 0, static_cast<float>(songTexts->size())));

		for (auto i = 0; i < songTexts->size(); i++) {
			songTexts->members[i]->targetY = i - curSelected;
		}
		if (change != 0) {
			sound::SoundManager::playSound("assets/sounds/scrollMenu.ogg");
		}
	}
} // namespace funkin::scenes
