#pragma once

#include "FunkinScene.hpp"
#include "funkin/Text.hpp"
#include "funkin/modding/LuaScript.hpp"
#include "funkin/objects/HealthIcon.hpp"
#include "funkin/ui/AlphabetList.hpp"
#include "nlohmann/json.hpp"

namespace funkin::scenes {
	struct FreeplaySong {
		std::string name;
		std::string icon;
		std::vector<std::string> difficulties;
		Color color;
		std::unordered_map<std::string, std::filesystem::path> charts;
		std::unordered_map<std::string, std::filesystem::path> metas;
	};

	class FreeplayScene : public FunkinScene {
	public:
		FreeplayScene();
		~FreeplayScene() override;
		std::vector<FreeplaySong> songs = {};
		std::shared_ptr<AlphabetList> songTexts = std::make_shared<AlphabetList>();
		std::vector<std::shared_ptr<objects::HealthIcon>> icons = {};

		std::shared_ptr<Sprite> menuBG = nullptr;
		std::shared_ptr<Text> difficultyText = nullptr;

		uint8_t currentDifficulty = 0;

		void update(float delta) override;

	protected:
		std::unique_ptr<modding::LuaScript> script = nullptr;
		void create() override;
	};
} // namespace funkin::scenes
