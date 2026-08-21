#include "LuaScript.hpp"

#include <iostream>
#include <utility>

#include "funkin/Game.hpp"
#include "funkin/objects/Character.hpp"
#include "funkin/objects/Stage.hpp"
#include "funkin/objects/notes/PlayField.hpp"
#include "raylib.h"

#define BIND(usertype, field, name) (lua_##usertype[#name] = field)
#define BIND_QUICK(usertype, field) BIND(usertype, field, field)

#define BIND_REF(usertype, field, name) (lua_##usertype[#name] = &field)
#define BIND_REF_QUICK(usertype, field) BIND_REF(usertype, field, field)

#define BIND_ENUM(field) {#field, field}

#define USERTYPE(type, name, ...) auto lua_##name = state.new_usertype<type>(#name __VA_ARGS__)
#define USERENUM(enum, name, ...) auto lua_##name = state.new_enum<enum>(#name, {__VA_ARGS__})

namespace funkin::modding {

	std::vector<LuaScript *> LuaScript::activeScripts = {};

	LuaScript::LuaScript(const std::string &path) {
		if (!FileExists(path.c_str())) {
			std::cerr << "File does not exist: " << path << std::endl;
			return;
		}

		closed = false;

		activeScripts.push_back(this);

		state.open_libraries(sol::lib::base, sol::lib::math);

		auto lua_raylib = state.new_usertype<void>("raylib");

		BIND_REF_QUICK(raylib, InitWindow);
		BIND_REF_QUICK(raylib, CloseWindow);
		BIND_REF_QUICK(raylib, WindowShouldClose);
		BIND_REF_QUICK(raylib, IsWindowReady);
		BIND_REF_QUICK(raylib, IsWindowFullscreen);
		BIND_REF_QUICK(raylib, IsWindowHidden);
		BIND_REF_QUICK(raylib, IsWindowMinimized);
		BIND_REF_QUICK(raylib, IsWindowMaximized);
		BIND_REF_QUICK(raylib, IsWindowFocused);
		BIND_REF_QUICK(raylib, IsWindowResized);
		BIND_REF_QUICK(raylib, IsWindowState);
		BIND_REF_QUICK(raylib, SetWindowState);
		BIND_REF_QUICK(raylib, ClearWindowState);
		BIND_REF_QUICK(raylib, ToggleFullscreen);
		BIND_REF_QUICK(raylib, ToggleBorderlessWindowed);
		BIND_REF_QUICK(raylib, MaximizeWindow);
		BIND_REF_QUICK(raylib, MinimizeWindow);
		BIND_REF_QUICK(raylib, RestoreWindow);
		BIND_REF_QUICK(raylib, SetWindowIcon);
		BIND_REF_QUICK(raylib, SetWindowIcons);
		BIND_REF_QUICK(raylib, SetWindowTitle);
		BIND_REF_QUICK(raylib, SetWindowPosition);
		BIND_REF_QUICK(raylib, SetWindowMonitor);
		BIND_REF_QUICK(raylib, SetWindowMinSize);
		BIND_REF_QUICK(raylib, SetWindowMaxSize);
		BIND_REF_QUICK(raylib, SetWindowSize);
		BIND_REF_QUICK(raylib, SetWindowOpacity);
		BIND_REF_QUICK(raylib, SetWindowFocused);
		BIND_REF_QUICK(raylib, GetWindowHandle);
		BIND_REF_QUICK(raylib, GetScreenWidth);
		BIND_REF_QUICK(raylib, GetScreenHeight);
		BIND_REF_QUICK(raylib, GetRenderWidth);
		BIND_REF_QUICK(raylib, GetRenderHeight);
		BIND_REF_QUICK(raylib, GetMonitorCount);
		BIND_REF_QUICK(raylib, GetCurrentMonitor);
		BIND_REF_QUICK(raylib, GetMonitorPosition);
		BIND_REF_QUICK(raylib, GetMonitorWidth);
		BIND_REF_QUICK(raylib, GetMonitorHeight);
		BIND_REF_QUICK(raylib, GetMonitorPhysicalWidth);
		BIND_REF_QUICK(raylib, GetMonitorPhysicalHeight);
		BIND_REF_QUICK(raylib, GetMonitorRefreshRate);
		BIND_REF_QUICK(raylib, GetWindowPosition);
		BIND_REF_QUICK(raylib, GetWindowScaleDPI);
		BIND_REF_QUICK(raylib, GetMonitorName);
		BIND_REF_QUICK(raylib, SetClipboardText);
		BIND_REF_QUICK(raylib, GetClipboardText);
		BIND_REF_QUICK(raylib, GetClipboardImage);
		BIND_REF_QUICK(raylib, EnableEventWaiting);
		BIND_REF_QUICK(raylib, DisableEventWaiting);

		BIND_REF_QUICK(raylib, ShowCursor);
		BIND_REF_QUICK(raylib, HideCursor);
		BIND_REF_QUICK(raylib, IsCursorHidden);
		BIND_REF_QUICK(raylib, EnableCursor);
		BIND_REF_QUICK(raylib, DisableCursor);
		BIND_REF_QUICK(raylib, IsCursorOnScreen);

		BIND_REF_QUICK(raylib, ColorNormalize);


		USERENUM(KeyboardKey, KeyboardKey, BIND_ENUM(KEY_UP), BIND_ENUM(KEY_DOWN), BIND_ENUM(KEY_LEFT), BIND_ENUM(KEY_RIGHT));


		USERENUM(BlendMode, BlendMode, BIND_ENUM(BLEND_ALPHA), BIND_ENUM(BLEND_ADDITIVE), BIND_ENUM(BLEND_MULTIPLIED),
				 BIND_ENUM(BLEND_ADD_COLORS), BIND_ENUM(BLEND_SUBTRACT_COLORS), BIND_ENUM(BLEND_ALPHA_PREMULTIPLY), BIND_ENUM(BLEND_CUSTOM),
				 BIND_ENUM(BLEND_CUSTOM_SEPARATE));

		USERENUM(ShaderUniformDataType, ShaderUniformDataType, BIND_ENUM(SHADER_UNIFORM_FLOAT), BIND_ENUM(SHADER_UNIFORM_VEC2),
				 BIND_ENUM(SHADER_UNIFORM_VEC3), BIND_ENUM(SHADER_UNIFORM_VEC4), BIND_ENUM(SHADER_UNIFORM_INT),
				 BIND_ENUM(SHADER_UNIFORM_IVEC2), BIND_ENUM(SHADER_UNIFORM_IVEC3), BIND_ENUM(SHADER_UNIFORM_IVEC4),
				 BIND_ENUM(SHADER_UNIFORM_UINT), BIND_ENUM(SHADER_UNIFORM_UIVEC2), BIND_ENUM(SHADER_UNIFORM_UIVEC3),
				 BIND_ENUM(SHADER_UNIFORM_UIVEC4), BIND_ENUM(SHADER_UNIFORM_SAMPLER2D));

		state["add"] = sol::overload(&Game::add<Sprite>, &Game::add<objects::notes::PlayField>);

		USERTYPE(Game, Game);
		BIND(Game, sol::var(std::ref(Game::defaultCamera)), defaultCamera);

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
				&Sprite::scale, "camera", &Sprite::camera, "angle", &Sprite::angle, "drawHitbox", &Sprite::drawHitbox, "alpha",
				&Sprite::alpha, "blend", &Sprite::blend, "offset", &Sprite::offset, "color", &Sprite::color, "updateHitbox",
				&Sprite::updateHitbox, "antialiasing", sol::property(&Sprite::getAntialiasing, &Sprite::setAntialiasing));

		auto character = state.new_usertype<objects::Character>(
				"Character", sol::constructors<objects::Character(float, float, std::string, objects::CharacterType)>(), "loadTexture",
				&objects::Character::loadTexture, "updateHitbox", &objects::Character::updateHitbox, "drawHitbox",
				&objects::Character::drawHitbox, "animation", &objects::Character::animation, "position", &objects::Character::position,
				"scale", &Sprite::scale, "hitbox", &objects::Character::hitbox, "offset", &objects::Character::offset, "barColor",
				&objects::Character::barColor, "texture", &objects::Character::texture, "dancesLeftAndRight",
				&objects::Character::dancesLeftAndRight, "cameraOffset", &objects::Character::cameraOffset, "angle",
				&objects::Character::angle, "antialiasing",
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
				"loadSparrow", &game::AnimationController::loadSparrow, "play",
				sol::overload(
						[](game::AnimationController &animationController, const std::string &name) { animationController.play(name); },
						[](game::AnimationController &animationController, const std::string &name, const bool force) {
							animationController.play(name, force);
						}),
				"isFinished", &game::AnimationController::isFinished);

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
		if (closed) {
			return;
		}

		if (!WindowShouldClose()) {
			call("onDestroy");
		}

		activeScripts.erase(std::ranges::find(activeScripts, this));

		closed = true;
	}

	size_t LuaScript::getMemoryUsage() const {
		if (closed) {
			return 0;
		}

		return sol::total_memory_used(state);
	}

	size_t LuaScript::getTotalMemoryUsage() {
		if (activeScripts.empty()) {
			return 0;
		}

		size_t mem = 0;

		for (const auto script: activeScripts) {
			mem += script->getMemoryUsage();
		}

		return mem;
	}
} // namespace funkin::modding
