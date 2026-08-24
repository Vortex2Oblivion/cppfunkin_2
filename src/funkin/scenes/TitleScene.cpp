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

		auto intoText = LoadFileText("assets/data/introText.txt");

		const std::vector<std::string> splashTexts = utilities::CoolUtil::split(intoText, "\n");

		UnloadFileText(intoText);

		const int currentSplash = GetRandomValue(0, static_cast<int>(splashTexts.size()) - 1);
		std::vector<std::string> currentSplashTexts = utilities::CoolUtil::split(splashTexts[currentSplash], "--");

		logoBumpin = std::make_shared<Sprite>(-150.0f, -100.0f);
		logoBumpin->loadTexture("assets/images/title/logoBumpin.png");
		logoBumpin->animation.loadSparrow("assets/images/title/logoBumpin.xml");
		logoBumpin->animation.addByPrefix("bump", "logo bumpin", 24);
		logoBumpin->animation.play("bump");

		gfDance = std::make_shared<Sprite>(static_cast<float>(GetRenderWidth()) * 0.4f, static_cast<float>(GetRenderHeight()) * 0.07f);
		gfDance->loadTexture("assets/images/title/gfDanceTitle.png");
		gfDance->animation.loadSparrow("assets/images/title/gfDanceTitle.xml");
		gfDance->animation.addByPrefix("danceLeft", "gfDance", 24, false, {30, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});
		gfDance->animation.addByPrefix("danceRight", "gfDance", 24, false, {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29});
		gfDance->animation.play("danceLeft");
		

		pressEnterText = std::make_shared<objects::Alphabet>(50.0f, 600.0f, "PRESS ENTER TO BEGIN");


		textGroup = std::make_shared<group::SpriteGroup<objects::Alphabet>>();
		add(textGroup);

		newgroundsLogo = std::make_shared<Sprite>(0, GetRenderHeight() * 0.52);
		if (utilities::CoolUtil::randomBool(30)) {
			newgroundsLogo->loadTexture("assets/images/title/newgrounds_logo_animated.png");
			newgroundsLogo->animation.addByRects("idle",
												 {Rectangle{.x = 0.0f, .y = 0.0f, .width = 600.0f, .height = 591.0f},
												  Rectangle{.x = 600.0f, .y = 0.0f, .width = 600.0f, .height = 591.0f}},
												 4, true);
			newgroundsLogo->animation.play("idle");
			newgroundsLogo->scale = Vector2{.x = 0.55f, .y = 0.55f};
			newgroundsLogo->position.y += 25.0f;
		} else {
			newgroundsLogo->loadTexture(utilities::CoolUtil::randomBool(1) ? "assets/images/title/newgrounds_logo_classic.png" : "assets/images/title/newgrounds_logo.png");
			newgroundsLogo->scale = Vector2{.x = 0.8f, .y = 0.8f};
		}

		newgroundsLogo->updateHitbox();
		newgroundsLogo->screenCenter(math::Axes::X);

		newgroundsLogo->visible = false;
		add(newgroundsLogo);


		conductor->onBeatHit.append([this, currentSplashTexts](auto beat) {
			if(!skippedIntro){
				switch (beat) {
					case 1:
						addIntroText("The");
						addIntroText("Funkin Crew Inc");
						break;
					case 3:
						addIntroText("presents");
						break;
					case 4:
						textGroup->clear();
						break;
					case 5:
						addIntroText("In association");
						addIntroText("with");
						break;
					case 7:
						addIntroText("newgrounds");
						newgroundsLogo->visible = true;
						break;
					case 8:
						textGroup->clear();
						newgroundsLogo->visible = false;
						break;
					case 9:
						addIntroText(currentSplashTexts[0]);
						break;
					case 11:
						addIntroText(currentSplashTexts[1]);
						break;
					case 12:
						textGroup->clear();
						break;
					case 13:
						addIntroText("Friday");
						break;
					case 14:
						// easter egg for when the game is trending with the wrong spelling
						// the random intro text would be "trending--only on x"
						addIntroText(currentSplashTexts[0] == "trending" ? "Nigth" : "Night");
						break;
					case 15:
						addIntroText("Funkin");
						break;
					case 16:
						skipIntro();
						break;
					default:
						break;
				}
			}

			gfDance->animation.play(beat % 2 == 0 ? "danceLeft" : "danceRight", true);
			logoBumpin->animation.play("bump");
		});

		conductor->tracks.push_back(LoadMusicStream("assets/music/freakyMenu.ogg"));
		conductor->bpm = 102;
		conductor->start();

		initialized = true;
	}

	void TitleScene::skipIntro() {
		if (skippedIntro) {
			return;
		}
		skippedIntro = true;
		remove(newgroundsLogo);
		remove(textGroup);
		Game::defaultCamera->flash(WHITE, initialized ? 1.0f : 4.0f);
		add(gfDance);
		add(logoBumpin);
		add(pressEnterText);
	}



	void TitleScene::addIntroText(const std::string &text) const {
		const auto alphabet = std::make_shared<objects::Alphabet>(50.0f, static_cast<float>(textGroup->size()) * 70.0f + 200.0f, text);
		textGroup->add(alphabet);
	}

	void TitleScene::update(const float delta) {
		FunkinScene::update(delta);
		if(!finishedFadeIn){
			if(conductor->time < 2000){
				SetMusicVolume(conductor->tracks[0],conductor->time/2000);
			}else{
				finishedFadeIn = true;
				SetMusicVolume(conductor->tracks[0],1);
			}
		}
		if(IsKeyPressed(KEY_ENTER)){
			if (skippedIntro) {
				Game::switchScene(std::make_unique<MainMenuScene>());
			}else if (initialized) {
				skipIntro();
			}
		}
	}
} // namespace funkin::scenes
