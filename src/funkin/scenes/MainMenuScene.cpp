#include "MainMenuScene.hpp"

#include "FreeplayScene.hpp"
#include "PlayScene.hpp"
#include "funkin/Game.hpp"
#include "funkin/objects/Alphabet.hpp"

namespace funkin::scenes {
	MainMenuScene::MainMenuScene() = default;

	MainMenuScene::~MainMenuScene() = default;

	void MainMenuScene::create() {
		FunkinScene::create();

		menuBG = std::make_shared<Sprite>();
		menuBG->loadTexture("assets/images/menuBG.png");
		menuBG->scale = Vector2{.x = 1.1f, .y = 1.1f};
		menuBG->screenCenter();
		menuBG->scrollFactor.y = 0.17f;
		add(menuBG);

		menuButtons = std::make_shared<Group<Sprite>>();
		add(menuButtons);

		constexpr float spacing = 160.0f;
		const float top = (static_cast<float>(GetRenderHeight()) - spacing * (static_cast<float>(menuItems.size()) - 1.0f)) / 2.0f;

		for (size_t i = 0; i < menuItems.size(); i++) {
			std::string item = menuItems[i];
			const auto menuButton = std::make_shared<Sprite>();
			menuButton->loadTexture("assets/images/mainmenu/" + item + ".png");
			menuButton->animation.loadSparrow("assets/images/mainmenu/" + item + ".xml");
			menuButton->animation.addByPrefix("idle", item + " idle", 24, true);
			menuButton->animation.addByPrefix("selected", item + " selected", 24, true);
			menuButton->animation.play("idle");
			menuButton->screenCenter(math::Axes::X);
			menuButton->position.y = top + spacing * static_cast<float>(i);
			menuButton->scrollFactor.y = 0.4f;
			menuButton->ID = i;
			menuButtons->add(menuButton);
		}

		changeSelection(0);
	}

	void MainMenuScene::update(const float delta) {
		FunkinScene::update(delta);
		if (IsKeyPressed(KEY_UP)) {
			changeSelection(-1);
		} else if (IsKeyPressed(KEY_DOWN)) {
			changeSelection(1);
		} else if (IsKeyPressed(KEY_ENTER)) {
			Game::switchScene(std::make_unique<FreeplayScene>());
		}
		Game::defaultCamera->target = Vector2Lerp(Game::defaultCamera->target, menuButtons->members[curSelected]->getMidpoint(),
												  1.0f - powf(1.0f - 0.06f, delta * 60.0f));
	}

	void MainMenuScene::changeSelection(const std::int8_t change) {
		curSelected = static_cast<std::uint8_t>(Wrap(static_cast<float>(curSelected + change), 0, static_cast<float>(menuItems.size())));
		for (size_t i = 0; i < menuItems.size(); i++) {
			const auto menuButton = menuButtons->members[i];
			if (menuButton->ID == static_cast<size_t>(curSelected)) {
				menuButton->animation.play("selected", true);
			} else{
				menuButton->animation.play("idle", true);
			}
			menuButton->updateHitbox();
			menuButton->screenCenter(math::Axes::X);
		}
	}
} // namespace funkin::scenes
