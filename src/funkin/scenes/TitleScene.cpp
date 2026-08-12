#include "TitleScene.hpp"

#include "MainMenuScene.hpp"
#include "funkin/Game.hpp"
#include "funkin/utilities/CoolUtil.hpp"

namespace funkin::scenes {
	bool TitleScene::initialized = false;

	TitleScene::TitleScene() = default;

	TitleScene::~TitleScene() = default;

	void TitleScene::create() {
		FunkinScene::create();

		const std::vector<std::string> splashTexts = utilities::CoolUtil::split(LoadFileText("assets/data/introText.txt"), "\n");

		const int currentSplash = GetRandomValue(0, static_cast<int>(splashTexts.size()) - 1);
		std::vector<std::string> currentSplashTexts = utilities::CoolUtil::split(splashTexts[currentSplash], "--");

		logoBumpin = std::make_shared<Sprite>(-150.0f, -100.0f);
		logoBumpin->loadTexture("assets/images/title/logoBumpin.png");
		logoBumpin->animation.loadSparrow("assets/images/title/logoBumpin.xml");
		logoBumpin->animation.addByPrefix("bump", "logo bumpin", 24);
		logoBumpin->animation.play("bump");
		add(logoBumpin);

		gfDance = std::make_shared<Sprite>(static_cast<float>(GetRenderWidth()) * 0.4f, static_cast<float>(GetRenderHeight()) * 0.07f);
		gfDance->loadTexture("assets/images/title/gfDanceTitle.png");
		gfDance->animation.loadSparrow("assets/images/title/gfDanceTitle.xml");
		gfDance->animation.addByPrefix("danceLeft", "gfDance", 24, false, {30, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});
		gfDance->animation.addByPrefix("danceRight", "gfDance", 24, false, {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29});
		gfDance->animation.play("danceLeft");
		add(gfDance);

		textGroup = std::make_shared<group::SpriteGroup<objects::Alphabet>>();
		add(textGroup);

		newgroundsLogo = std::make_shared<Sprite>(0, GetRenderHeight() * 0.52);

		if (utilities::CoolUtil::randomBool(1)) {
			newgroundsLogo->loadTexture("assets/images/title/newgrounds_logo_classic.png");
		} else if (utilities::CoolUtil::randomBool(30)) {
			newgroundsLogo->loadTexture("assets/images/title/newgrounds_logo_animated.png");
			newgroundsLogo->animation.addByRects("idle",
												 {Rectangle{.x = 0.0f, .y = 0.0f, .width = 600.0f, .height = 591.0f},
												  Rectangle{.x = 600.0f, .y = 0.0f, .width = 600.0f, .height = 591.0f}},
												 4, true);
			newgroundsLogo->animation.play("idle");
			newgroundsLogo->scale = Vector2{.x = 0.55f, .y = 0.55f};
			newgroundsLogo->position.y += 25.0f;
		} else {
			newgroundsLogo->loadTexture("assets/images/title/newgrounds_logo.png");
			newgroundsLogo->scale = Vector2{.x = 0.8f, .y = 0.8f};
		}

		newgroundsLogo->updateHitbox();
		newgroundsLogo->screenCenter(math::Axes::X);

		newgroundsLogo->visible = false;
		add(newgroundsLogo);

		conductor->onBeatHit.append([this, currentSplashTexts](auto beat) {
			switch (beat) {
				case 1:
					createCoolText({"The", "Funkin Crew Inc"});
					break;
				case 3:
					addMoreText("presents");
					break;
				case 4:
					textGroup->clear();
					break;
				case 5:
					createCoolText({"In association", "with"});
					break;
				case 7:
					addMoreText("newgrounds");
					newgroundsLogo->visible = true;
					break;
				case 8:
					textGroup->clear();
					remove(newgroundsLogo);
					break;
				case 9:
					addMoreText(currentSplashTexts[0]);
					break;
				case 11:
					addMoreText(currentSplashTexts[1]);
					break;
				case 12:
					textGroup->clear();
					break;
				case 13:
					addMoreText("Friday");
					break;
				case 14:
					// easter egg for when the game is trending with the wrong spelling
					// the random intro text would be "trending--only on x"
					addMoreText(currentSplashTexts[0] == "trending" ? "Nigth" : "Night");
					break;
				case 15:
					addMoreText("Funkin");
					break;
				case 16:
					skipIntro();
					break;
				default:
					break;
			}

			danceLeft = !danceLeft;

			if (danceLeft) {
				gfDance->animation.play("danceLeft", true);
			} else {
				gfDance->animation.play("danceRight", true);
			}

			logoBumpin->animation.play("bump");
		});

		conductor->tracks.push_back(LoadMusicStream("assets/music/freakyMenu.ogg"));
		conductor->bpm = 102;
		conductor->start();

		if (initialized) {
		}
		initialized = true;
	}

	void TitleScene::skipIntro() {
		if (skippedIntro) {
			return;
		}
		remove(newgroundsLogo);
		remove(textGroup);
		Game::defaultCamera->flash(WHITE, initialized ? 1.0f : 4.0f);
		skippedIntro = true;
	}


	void TitleScene::createCoolText(const std::vector<std::string> &textArray) const {
		for (size_t i = 0; i < textArray.size(); i++) {
			const auto alphabet = std::make_shared<objects::Alphabet>(0.0f, static_cast<float>(i) * 60.0f + 200.0f, textArray[i]);
			textGroup->add(alphabet);
		}
	}

	void TitleScene::addMoreText(const std::string &text) const {
		const auto alphabet = std::make_shared<objects::Alphabet>(0.0f, static_cast<float>(textGroup->size()) * 60.0f + 200.0f, text);
		textGroup->add(alphabet);
	}

	void TitleScene::update(const float delta) {
		FunkinScene::update(delta);

		if (IsKeyPressed(KEY_ENTER) && skippedIntro) {
			Game::switchScene(std::make_unique<MainMenuScene>());
		}

		if (IsKeyPressed(KEY_ENTER) && !skippedIntro && initialized) {
			skipIntro();
		}
	}
} // namespace funkin::scenes
