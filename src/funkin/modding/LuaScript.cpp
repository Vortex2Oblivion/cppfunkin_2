#include "LuaScript.hpp"

#include <iostream>
#include <utility>

#include "Game.hpp"
#include "PlayScene.hpp"
#include "Sprite.hpp"
#include "Stage.hpp"
#include "game/AnimationController.hpp"
#include "notes/PlayField.hpp"
#include "objects/Character.hpp"

namespace funkin::modding {
	LuaScript::LuaScript(const std::string &path) {
		if (!FileExists(path.c_str())) {
			std::cerr << "File does not exist: " << path << std::endl;
			return;
		}
		state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);

		state["add"] = sol::overload(&Game::add<Sprite>, &Game::add<objects::notes::PlayField>);
		state["parseSong"] = &data::Song::parseSong;

		state.new_usertype<Game>("Game", "defaultCamera", sol::var(std::ref(Game::defaultCamera)));

		sol::usertype<objects::Stage> lua_Stage = state.new_usertype<objects::Stage>(
				"Stage", sol::constructors<objects::Stage(std::string)>(), "stageName", &objects::Stage::stageName,
				"add", sol::overload(&objects::Stage::add<Sprite>, &objects::Stage::add<objects::Character>));

		state.new_usertype<Camera>("Camera", sol::constructors<Camera()>(), "zoom", &Camera::zoom, "angle",
								   &Camera::angle, "target", &Camera::target, "position", &Camera::position);

		state.new_usertype<Sprite>("Sprite",
									"new", [](float x, float y) {
										return std::make_shared<Sprite>(x, y);
									},
								   	"loadTexture", &Sprite::loadTexture,
								   	"animation", &Sprite::animation,
								   	"position", &Sprite::position,
								   	"scrollFactor", &Sprite::scrollFactor);

		state.new_usertype<objects::Character>(
				"Character", sol::constructors<objects::Character(float, float, std::string, objects::CharacterType)>(),
				"loadTexture", &objects::Character::loadTexture,
				"animation", &objects::Character::animation,
				"position", &objects::Character::position);

		state.new_usertype<game::AnimationController>(
				"AnimationController", sol::constructors<game::AnimationController()>(), "addByPrefix",
				sol::overload(
						[](game::AnimationController &animationController, const std::string &name, const std::string &prefix,
							const std::uint8_t framerate, const bool looped, sol::table indices) {
							animationController.addByPrefix(name, prefix, framerate, looped, tableToVector<std::uint8_t>(std::move(indices)));
						},
						&game::AnimationController::addByPrefix),
				"addOffset", [](game::AnimationController &animationController, const std::string &name, const float x, const float y) {
					animationController.addOffset(name, x, y);
				},
				"loadSparrow", &game::AnimationController::loadSparrow,
				"play", &game::AnimationController::play,
				"isFinished", &game::AnimationController::isFinished);

		sol::usertype<data::Song> lua_Song = state.new_usertype<data::Song>("Song");
		lua_Song["parseSong"] = &data::Song::parseSong;


		state.new_usertype<data::SongData>("SongData", sol::constructors<data::SongData()>(), "speed",
										   &data::SongData::speed, "bpm", &data::SongData::bpm, "playerNotes",
										   &data::SongData::playerNotes, "opponentNotes",
										   &data::SongData::opponentNotes);

		state.new_usertype<Vector2>("Vector2", sol::constructors<Vector2()>(), "x", &Vector2::x, "y", &Vector2::y);

		sol::usertype<objects::notes::PlayField> lua_PlayField = state.new_usertype<objects::notes::PlayField>(
				"PlayField",
				sol::constructors<
						objects::notes::PlayField(), objects::notes::PlayField(float),
						objects::notes::PlayField(float, float), objects::notes::PlayField(float, float, std::uint8_t),
						objects::notes::PlayField(float, float, std::uint8_t, float),
						objects::notes::PlayField(float, float, std::uint8_t, float, std::vector<data::NoteData>),
						objects::notes::PlayField(float, float, std::uint8_t, float, std::vector<data::NoteData>,
												  std::shared_ptr<game::Conductor>)>());
		lua_PlayField["botplay"] =
				sol::property(&objects::notes::PlayField::getBotplay, &objects::notes::PlayField::setBotplay);
		lua_PlayField["camera"] = sol::property(&objects::notes::PlayField::camera);
		lua_PlayField["position"] = sol::property(&objects::notes::PlayField::position);

		state.script_file(path);
		call("onCreate");
	}

	LuaScript::~LuaScript() {
		call("onDestroy");
	}
} // namespace funkin::modding
