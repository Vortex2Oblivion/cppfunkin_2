#pragma once

#include "funkin/Scene.hpp"
#include "funkin/Text.hpp"
#include "funkin/data/Song.hpp"
#include "funkin/game/Conductor.hpp"
#include "funkin/modding/LuaScript.hpp"
#include "funkin/objects/HealthBar.hpp"
#include "funkin/objects/Stage.hpp"
#include "funkin/objects/notes/PlayField.hpp"


namespace funkin::scenes {
	using namespace game;

	class PlayScene : public Scene {
	public:
		explicit PlayScene(const std::string &songName,const std::string &difficulty);
		~PlayScene() override;

		std::shared_ptr<Conductor> conductor = nullptr;
		std::vector<Music> tracks = {};
		data::SongData songData = {};
		std::vector<data::EventData> events = {};
		std::string difficulty;
		std::string songName;
		Music inst = {};
		Music voices = {};
		Music voicesPlayer = {};

		std::shared_ptr<objects::HealthBar> healthBar = nullptr;
		std::shared_ptr<Text> scoreText = nullptr;

		bool easingCameraZoom = false;

		float defaultZoom = 1.0f;
		float zoomIntensity = 0.03f;

		float defaultHUDZoom = 1.0f;
		float hudZoomIntensity = 0.03f;

		std::shared_ptr<Camera> camHUD = nullptr;

		std::shared_ptr<objects::Stage> stage = nullptr;

		std::shared_ptr<objects::Character> dad = nullptr;
		std::shared_ptr<objects::Character> boyfriend = nullptr;
		std::shared_ptr<objects::Character> girlfriend = nullptr;

		std::shared_ptr<objects::notes::PlayField> playerField = nullptr;
		std::shared_ptr<objects::notes::PlayField> opponentField = nullptr;

		std::vector<std::shared_ptr<modding::LuaScript>> scripts = {};

		void update(float delta) override;

		template<typename... Args>
		void callOnScripts(const std::string &name, Args... args) {
			for (const auto &script: scripts) {
				script->call(name, args...);
			}
		}

		template<typename T>
		void setOnScripts(const std::string &name, T type) {
			for (const auto &script: scripts) {
				script->set(name, type);
			}
		}

	protected:
		void create() override;
		void updateScoreText() const;
	};
} // namespace funkin::scenes
