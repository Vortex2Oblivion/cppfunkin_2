#include "PauseSubScene.hpp"

#include "PlayScene.hpp"
#include "FunkinScene.hpp"
#include "funkin/Scene.hpp"
#include "MainMenuScene.hpp"
#include "FreeplayScene.hpp"
#include "funkin/ui/AlphabetList.hpp"
#include "funkin/game/Conductor.hpp"
#include "funkin/Game.hpp"
#include "funkin/Group.hpp"
#include "raylib.h"
using Conductor = funkin::game::Conductor;

namespace funkin::scenes {
	PauseSubScene::PauseSubScene(std::string _songName,std::string _difficulty) {
		this->songName = _songName;
		this->difficulty = _difficulty;
		for (size_t i = 0; i < menuOptions.size(); i++) {
			menuAlphabets->add(std::make_shared<objects::Alphabet>(90, 250, menuOptions[i]));
		}
		add(menuAlphabets);
		menuAlphabets->changeSelection(0);
	}
	PauseSubScene::~PauseSubScene() {}
	void PauseSubScene::close() {
		pending_close=true;
		// parentScene->remove(this);
	}
	void PauseSubScene::restart() {
		Game::switchScene(std::make_unique<PlayScene>(songName,difficulty));
	}
	void PauseSubScene::exit() {
		Game::switchScene(std::make_unique<FreeplayScene>());
	}
	void PauseSubScene::update(const float delta) {
		Scene::update(delta);
		menuAlphabets->checkInput();
		if (IsKeyPressed(KEY_ENTER)) {
			switch(menuAlphabets->currentSelected){
				case 0:{
					close();
					return;
				}
				case 1:{
					restart();
					return;
				}
				case 2:{
					exit();
					return;
				}
			}
			// Game::switchScene(std::make_unique<PlayScene>(songTexts->members[curSelected]->getText(),difficulties[curSelected][curDifficulty]));
		}else if (IsKeyPressed(KEY_BACKSPACE)) {
			exit();
		}
	}
} // namespace funkin::scenes
