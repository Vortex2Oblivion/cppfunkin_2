#include "LuaScript.hpp"

#include <iostream>
#include <utility>

#include "funkin/Game.hpp"
#include "funkin/objects/Character.hpp"
#include "funkin/objects/Stage.hpp"
#include "funkin/objects/notes/PlayField.hpp"
#include "raylib.h"

#define BIND_FIELD(field) #field, &field

namespace funkin::modding {
	LuaScript::LuaScript(const std::string &path) {

		if (!FileExists(path.c_str())) {
			std::cerr << "File does not exist: " << path << std::endl;
			return;
		}

		state.open_libraries(sol::lib::base, sol::lib::math);

		state.new_usertype<void>(
				"raylib", BIND_FIELD(InitWindow), BIND_FIELD(CloseWindow), BIND_FIELD(WindowShouldClose), BIND_FIELD(IsWindowReady),
				BIND_FIELD(IsWindowFullscreen), BIND_FIELD(IsWindowHidden), BIND_FIELD(IsWindowMinimized), BIND_FIELD(IsWindowMaximized),
				BIND_FIELD(IsWindowFocused), BIND_FIELD(IsWindowResized), BIND_FIELD(IsWindowState), BIND_FIELD(SetWindowState),
				BIND_FIELD(ClearWindowState), BIND_FIELD(ToggleFullscreen), BIND_FIELD(ToggleBorderlessWindowed),
				BIND_FIELD(MaximizeWindow), BIND_FIELD(MinimizeWindow), BIND_FIELD(RestoreWindow), BIND_FIELD(ColorNormalize));


		state.new_enum<BlendMode>("BlendMode", {{"BLEND_ALPHA", BLEND_ALPHA},
												{"BLEND_ADDITIVE", BLEND_ADDITIVE},
												{"BLEND_MULTIPLIED", BLEND_MULTIPLIED},
												{"BLEND_ADD_COLORS", BLEND_ADD_COLORS},
												{"BLEND_SUBTRACT_COLORS", BLEND_SUBTRACT_COLORS},
												{"BLEND_ALPHA_PREMULTIPLY", BLEND_ALPHA_PREMULTIPLY}});

		state.new_enum<ShaderUniformDataType>("ShaderUniformDataType", {{"SHADER_UNIFORM_FLOAT", SHADER_UNIFORM_FLOAT},
																		{"SHADER_UNIFORM_VEC2", SHADER_UNIFORM_VEC2},
																		{"SHADER_UNIFORM_VEC3", SHADER_UNIFORM_VEC3},
																		{"SHADER_UNIFORM_VEC4", SHADER_UNIFORM_VEC4},
																		{"SHADER_UNIFORM_INT", SHADER_UNIFORM_INT},
																		{"SHADER_UNIFORM_IVEC2", SHADER_UNIFORM_IVEC2},
																		{"SHADER_UNIFORM_IVEC3", SHADER_UNIFORM_IVEC3},
																		{"SHADER_UNIFORM_IVEC4", SHADER_UNIFORM_IVEC4}});

		state["add"] = sol::overload(&Game::add<Sprite>, &Game::add<objects::notes::PlayField>);
		state["parseSong"] = &data::Song::parseSong;

		state.new_usertype<Game>("Game", "defaultCamera", sol::var(std::ref(Game::defaultCamera)));

		state.new_usertype<objects::Stage>("Stage", sol::constructors<objects::Stage(std::string)>(), "stageName",
										   &objects::Stage::stageName, "add",
										   sol::overload(&objects::Stage::add<Sprite>, &objects::Stage::add<objects::Character>),
										   "snapToPosition", &objects::Stage::snapToPosition);

		state.new_usertype<Camera>("Camera", sol::constructors<Camera()>(), "zoom", &Camera::zoom, "angle", &Camera::angle, "target",
								   &Camera::target, "position", &Camera::position);

#define SHADER_SET_VALUE_TYPE(t)                                                                                                           \
	[](const std::shared_ptr<graphics::Shader> &shader, const std::string &uniform, const t value,                                         \
	   const ShaderUniformDataType uniformType) { shader->setValue(uniform, value, uniformType); }

		state.new_usertype<graphics::Shader>(
				"Shader", "new", [](const std::string &fragmentPath) { return std::make_shared<graphics::Shader>(fragmentPath); },
				"setValue",
				sol::overload(SHADER_SET_VALUE_TYPE(float), SHADER_SET_VALUE_TYPE(Vector2), SHADER_SET_VALUE_TYPE(Vector3),
							  SHADER_SET_VALUE_TYPE(Vector4), SHADER_SET_VALUE_TYPE(Color)));

		state.new_usertype<Sprite>(
				"Sprite", "new", [](float x, float y) { return std::make_shared<Sprite>(x, y); }, "loadTexture", &Sprite::loadTexture,
				"animation", &Sprite::animation, "position", &Sprite::position, "scrollFactor", &Sprite::scrollFactor, "scale",
				&Sprite::scale, "angle", &Sprite::angle, "alpha", &Sprite::alpha, "blend", &Sprite::blend, "antialiasing",
				sol::property(&Sprite::getAntialiasing, &Sprite::setAntialiasing));

		auto character = state.new_usertype<objects::Character>(
				"Character", sol::constructors<objects::Character(float, float, std::string, objects::CharacterType)>(), "loadTexture",
				&objects::Character::loadTexture, "updateHitbox", &objects::Character::updateHitbox, "drawHitbox",
				&objects::Character::drawHitbox, "animation", &objects::Character::animation, "position", &objects::Character::position,
				"scale", &objects::Character::scale, "offset", &objects::Character::offset, "barColor", &objects::Character::barColor,
				"texture", &objects::Character::texture, "dancesLeftAndRight", &objects::Character::dancesLeftAndRight, "antialiasing",
				sol::property(&objects::Character::getAntialiasing, &objects::Character::setAntialiasing));

		character["shaders"] = sol::property([](objects::Character &c) { return c.shaders; },
											 [](objects::Character &c, const sol::table &shaders) {
												 c.shaders = tableToVector<std::shared_ptr<graphics::Shader>>(shaders);
											 });

		state.new_usertype<game::AnimationController>(
				"AnimationController", sol::constructors<game::AnimationController(Sprite *)>(), "addByPrefix",
				sol::overload(
						[](game::AnimationController &animationController, const std::string &name, const std::string &prefix,
						   const std::uint8_t framerate, const bool looped, sol::table indices) {
							animationController.addByPrefix(name, prefix, framerate, looped,
															tableToVector<std::uint8_t>(std::move(indices)));
						},
						&game::AnimationController::addByPrefix),
				"addOffset",
				[](game::AnimationController &animationController, const std::string &name, const float x, const float y) {
					animationController.addOffset(name, x, y);
				},
				"loadSparrow", &game::AnimationController::loadSparrow, "play", &game::AnimationController::play, "isFinished",
				&game::AnimationController::isFinished);

		sol::usertype<data::Song> lua_Song = state.new_usertype<data::Song>("Song");
		lua_Song["parseSong"] = &data::Song::parseSong;


		state.new_usertype<data::SongData>("SongData", sol::constructors<data::SongData()>(), "speed", &data::SongData::speed, "bpm",
										   &data::SongData::bpm, "playerNotes", &data::SongData::playerNotes, "opponentNotes",
										   &data::SongData::opponentNotes);

		state.new_usertype<Vector2>("Vector2", sol::constructors<Vector2(), Vector2(float), Vector2(float, float)>(), "x", &Vector2::x, "y",
									&Vector2::y);

		state.new_usertype<Vector3>("Vector3",
									sol::constructors<Vector3(), Vector3(float), Vector3(float, float), Vector3(float, float, float)>(),
									"x", &Vector3::x, "y", &Vector3::y, "z", &Vector3::z);

		state.new_usertype<Vector4>("Vector4",
									sol::constructors<Vector4(), Vector4(float), Vector4(float, float), Vector4(float, float, float),
													  Vector4(float, float, float, float)>(),
									"x", &Vector4::x, "y", &Vector4::y, "z", &Vector4::z, "w", &Vector4::w);

		state.new_usertype<Color>("Color",
								  sol::constructors<Color(), Color(unsigned char, unsigned char, unsigned char),
													Color(unsigned char, unsigned char, unsigned char, unsigned char)>(),
								  "r", &Color::r, "g", &Color::g, "b", &Color::b, "a", &Color::a);

		state.new_usertype<Texture>("Texture", "id", &Texture::id, "width", &Texture::width, "height", &Texture::height, "mipmaps",
									&Texture::mipmaps, "format", &Texture::format);

		state.new_usertype<objects::notes::PlayField>(
				"PlayField", "new",
				[](const float x, const float y, const std::uint8_t keyCount, const float speed, const sol::table &noteDatas,
				   const std::shared_ptr<game::Conductor> &conductor) {
					return std::make_shared<objects::notes::PlayField>(x, y, keyCount, speed, tableToVector<data::NoteData>(noteDatas),
																	   conductor);
				},
				"botplay", sol::property(&objects::notes::PlayField::getBotplay, &objects::notes::PlayField::setBotplay), "camera",
				&objects::notes::PlayField::camera, "position", &objects::notes::PlayField::position, "scale",
				&objects::notes::PlayField::scale, "skew", &objects::notes::PlayField::skew, "origin", &objects::notes::PlayField::origin);

		state.script_file(path);
		call("onCreate");
	}

	LuaScript::~LuaScript() {
		if (!WindowShouldClose()) {
			call("onDestroy");
		}
	}
} // namespace funkin::modding
