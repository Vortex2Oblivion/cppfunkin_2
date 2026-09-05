#include "PauseSubScene.hpp"

#include "FreeplayScene.hpp"
#include "FunkinScene.hpp"
#include "MainMenuScene.hpp"
#include "PlayScene.hpp"
#include "funkin/Game.hpp"
#include "funkin/Group.hpp"
#include "funkin/Scene.hpp"
#include "funkin/game/Conductor.hpp"
#include "funkin/ui/AlphabetList.hpp"
#include "raylib.h"
using Conductor = funkin::game::Conductor;

namespace funkin::scenes {
	PauseSubScene::PauseSubScene(const std::string &_songName, const std::string &_difficulty) {
		this->songName = _songName;
		this->difficulty = _difficulty;
		for (auto &menuOption: menuOptions) {
			menuAlphabets->add(std::make_shared<objects::Alphabet>(90, 250, menuOption));
		}
		add(menuAlphabets);
		menuAlphabets->changeSelection(0);
	}

	PauseSubScene::~PauseSubScene() = default;

	void PauseSubScene::close() {
		pending_close = true;
		Game::defaultCamera->flashAlpha = 0.5;
		Game::defaultCamera->flashColor = BLACK;
		Game::defaultCamera->flashDuration = 0.1;
		// parentScene->remove(this);
	}
	void PauseSubScene::restart() { Game::switchScene(std::make_unique<PlayScene>(songName, difficulty)); }

	void PauseSubScene::exit() { Game::switchScene(std::make_unique<FreeplayScene>()); }

	void PauseSubScene::draw(const float x, const float y, const std::shared_ptr<Camera> &cam) {
		DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), ColorAlpha(BLACK, 0.5));
		Scene::draw(x, y, cam);
	}
	void PauseSubScene::update(const float delta) {
		Scene::update(delta);
		menuAlphabets->checkInput();
		if (IsKeyPressed(KEY_ENTER)) {
			switch (menuAlphabets->currentSelected) {
				case 0: {
					close();
					return;
				}
				case 1: {
					restart();
					return;
				}
				case 2: {
					exit();
				}
				default:
					break;
			}
			// Game::switchScene(std::make_unique<PlayScene>(songTexts->members[curSelected]->getText(),difficulties[curSelected][curDifficulty]));
		} else if (IsKeyPressed(KEY_BACKSPACE)) {
			exit();
		}
	}
} // namespace funkin::scenes
