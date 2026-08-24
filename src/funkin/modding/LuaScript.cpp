#include "LuaScript.hpp"

#include <iostream>

#include "funkin/Game.hpp"
#include "funkin/objects/Stage.hpp"
#include "raylib.h"

namespace funkin::modding {

	std::vector<LuaScript *> LuaScript::activeScripts = {};

	/*	namespace {
			struct FieldShit {
				std::string name;
				sol::object field;
			};
		} // namespace

		static std::unordered_map<std::string, std::vector<FieldShit>> classFields = {};

	#define BIND_FIELD(field) #field, &field

	#define BIND_CLASS(class, name, state) \
		classFields[#name] = {}; \ auto lua_##name = state.new_usertype<class>(#name);

	#define BIND_CLASS_FIELD(className, fieldVal, fieldName) \
		auto _lua_##className##_##fieldName = sol::make_object(state, fieldVal); \
		lua_##className.set(#fieldName, fieldVal); \ classFields[#className].push_back(FieldShit{.name = #fieldName, .field =
	_lua_##className##_##fieldName});

	#define BIND_SUBCLASS(class, className, superclassName, state) \
		classFields[#className] = {}; \
		auto lua_##className = state.new_usertype<class>(#className); \
		for (const auto &[name, field]: classFields[#superclassName]) { \
			lua_##className.set(name, field); \
		}*/

	LuaScript::LuaScript(const std::string &path) {
		if (!FileExists(path.c_str())) {
			std::cerr << "File does not exist: " << path << std::endl;
			return;
		}

		closed = false;

		activeScripts.push_back(this);

		state.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::debug,
							 sol::lib::bit32, sol::lib::io, sol::lib::utf8);

#define BIND(v) set(#v, &v);
#define BIND_ENUM(field)                                                                                                                   \
	{                                                                                                                                      \
		#field, field                                                                                                                      \
	}

		// raylib
		auto lua_raylib = state.new_usertype<void>("raylib");
		lua_raylib.BIND(InitWindow);
		lua_raylib.BIND(CloseWindow);
		lua_raylib.BIND(WindowShouldClose);
		lua_raylib.BIND(IsWindowReady);
		lua_raylib.BIND(IsWindowFullscreen);
		lua_raylib.BIND(IsWindowHidden);
		lua_raylib.BIND(IsWindowMinimized);
		lua_raylib.BIND(IsWindowMaximized);
		lua_raylib.BIND(IsWindowFocused);
		lua_raylib.BIND(IsWindowResized);
		lua_raylib.BIND(IsWindowState);
		lua_raylib.BIND(SetWindowState);
		lua_raylib.BIND(ClearWindowState);
		lua_raylib.BIND(ToggleFullscreen);
		lua_raylib.BIND(ToggleBorderlessWindowed);
		lua_raylib.BIND(MaximizeWindow);
		lua_raylib.BIND(MinimizeWindow);
		lua_raylib.BIND(RestoreWindow);
		lua_raylib.BIND(SetWindowIcon);
		lua_raylib.BIND(SetWindowIcons);
		lua_raylib.BIND(SetWindowTitle);
		lua_raylib.BIND(SetWindowPosition);
		lua_raylib.BIND(SetWindowMonitor);
		lua_raylib.BIND(SetWindowMinSize);
		lua_raylib.BIND(SetWindowMaxSize);
		lua_raylib.BIND(SetWindowSize);
		lua_raylib.BIND(SetWindowOpacity);
		lua_raylib.BIND(SetWindowFocused);
		lua_raylib.BIND(GetWindowHandle);
		lua_raylib.BIND(GetScreenWidth);
		lua_raylib.BIND(GetScreenHeight);
		lua_raylib.BIND(GetRenderWidth);
		lua_raylib.BIND(GetRenderHeight);
		lua_raylib.BIND(GetMonitorCount);
		lua_raylib.BIND(GetCurrentMonitor);
		lua_raylib.BIND(GetMonitorPosition);
		lua_raylib.BIND(GetMonitorWidth);
		lua_raylib.BIND(GetMonitorHeight);
		lua_raylib.BIND(GetMonitorPhysicalWidth);
		lua_raylib.BIND(GetMonitorPhysicalHeight);
		lua_raylib.BIND(GetMonitorRefreshRate);
		lua_raylib.BIND(GetWindowPosition);
		lua_raylib.BIND(GetWindowScaleDPI);
		lua_raylib.BIND(GetMonitorName);
		lua_raylib.BIND(SetClipboardText);
		lua_raylib.BIND(GetClipboardText);
		lua_raylib.BIND(GetClipboardImage);
		lua_raylib.BIND(EnableEventWaiting);
		lua_raylib.BIND(DisableEventWaiting);

		lua_raylib.BIND(ShowCursor);
		lua_raylib.BIND(HideCursor);
		lua_raylib.BIND(IsCursorHidden);
		lua_raylib.BIND(EnableCursor);
		lua_raylib.BIND(DisableCursor);
		lua_raylib.BIND(IsCursorOnScreen);

		lua_raylib.BIND(ColorIsEqual);
		lua_raylib.BIND(Fade);
		lua_raylib.BIND(ColorToInt);
		lua_raylib.BIND(ColorNormalize);
		lua_raylib.BIND(ColorFromNormalized);
		lua_raylib.BIND(ColorToHSV);
		lua_raylib.BIND(ColorFromHSV);
		lua_raylib.BIND(ColorTint);
		lua_raylib.BIND(ColorBrightness);
		lua_raylib.BIND(ColorContrast);
		lua_raylib.BIND(ColorAlpha);
		lua_raylib.BIND(ColorAlphaBlend);
		lua_raylib.BIND(ColorLerp);
		lua_raylib.BIND(GetColor);
		lua_raylib.BIND(GetPixelColor);
		lua_raylib.BIND(SetPixelColor);
		lua_raylib.BIND(GetPixelDataSize);

		state["raylib"]["LIGHTGRAY"] = LIGHTGRAY;
		state["raylib"]["GRAY"] = GRAY;
		state["raylib"]["DARKGRAY"] = DARKGRAY;
		state["raylib"]["YELLOW"] = YELLOW;
		state["raylib"]["GOLD"] = GOLD;
		state["raylib"]["ORANGE"] = ORANGE;
		state["raylib"]["PINK"] = PINK;
		state["raylib"]["RED"] = RED;
		state["raylib"]["MAROON"] = MAROON;
		state["raylib"]["GREEN"] = GREEN;
		state["raylib"]["LIME"] = LIME;
		state["raylib"]["DARKGREEN"] = DARKGREEN;
		state["raylib"]["SKYBLUE"] = SKYBLUE;
		state["raylib"]["BLUE"] = BLUE;
		state["raylib"]["DARKBLUE"] = DARKBLUE;
		state["raylib"]["PURPLE"] = PURPLE;
		state["raylib"]["VIOLET"] = VIOLET;
		state["raylib"]["DARKPURPLE"] = DARKPURPLE;
		state["raylib"]["BEIGE"] = BEIGE;
		state["raylib"]["BROWN"] = BROWN;
		state["raylib"]["DARKBROWN"] = DARKBROWN;

		state["raylib"]["WHITE"] = WHITE;
		state["raylib"]["BLACK"] = BLACK;
		state["raylib"]["BLANK"] = BLANK;
		state["raylib"]["MAGENTA"] = MAGENTA;
		state["raylib"]["RAYWHITE"] = RAYWHITE;

		auto lua_Vector2 = state.new_usertype<Vector2>("Vector2");
		lua_Vector2.set("new", sol::constructors<Vector2(float, float)>());
		lua_Vector2.set("x", &Vector2::x);
		lua_Vector2.set("y", &Vector2::y);

		auto lua_Vector3 = state.new_usertype<Vector3>("Vector3");
		lua_Vector3.set("new", sol::constructors<Vector3(float, float, float)>());
		lua_Vector3.set("x", &Vector3::x);
		lua_Vector3.set("y", &Vector3::y);
		lua_Vector3.set("z", &Vector3::z);

		auto lua_Vector4 = state.new_usertype<Vector4>("Vector4");
		lua_Vector4.set("new", sol::constructors<Vector4(float, float, float, float)>());
		lua_Vector4.set("x", &Vector4::x);
		lua_Vector4.set("y", &Vector4::y);
		lua_Vector4.set("z", &Vector4::z);
		lua_Vector4.set("w", &Vector4::w);

		auto lua_Matrix = state.new_usertype<Matrix>("Matrix");
		lua_Matrix.set("new", sol::constructors<Matrix(float, float, float, float, float, float, float, float, float, float, float, float,
													   float, float, float, float)>());
		lua_Matrix.set("m0", &Matrix::m0);
		lua_Matrix.set("m1", &Matrix::m1);
		lua_Matrix.set("m2", &Matrix::m2);
		lua_Matrix.set("m3", &Matrix::m3);
		lua_Matrix.set("m4", &Matrix::m4);
		lua_Matrix.set("m5", &Matrix::m5);
		lua_Matrix.set("m6", &Matrix::m6);
		lua_Matrix.set("m7", &Matrix::m7);
		lua_Matrix.set("m8", &Matrix::m8);
		lua_Matrix.set("m9", &Matrix::m9);
		lua_Matrix.set("m10", &Matrix::m10);
		lua_Matrix.set("m11", &Matrix::m11);
		lua_Matrix.set("m12", &Matrix::m12);
		lua_Matrix.set("m13", &Matrix::m13);
		lua_Matrix.set("m14", &Matrix::m14);
		lua_Matrix.set("m15", &Matrix::m15);


		auto lua_Color = state.new_usertype<Color>("Color");
		lua_Color.set("new", sol::constructors<Color(u_char, u_char, u_char, u_char)>());
		lua_Color.set("r", &Color::r);
		lua_Color.set("g", &Color::g);
		lua_Color.set("b", &Color::b);
		lua_Color.set("a", &Color::a);

		auto lua_Rectangle = state.new_usertype<Rectangle>("Rectangle");
		lua_Rectangle.set("new", sol::constructors<Rectangle(float, float, float, float)>());
		lua_Rectangle.set("x", &Rectangle::x);
		lua_Rectangle.set("y", &Rectangle::y);
		lua_Rectangle.set("width", &Rectangle::width);
		lua_Rectangle.set("height", &Rectangle::height);

		auto lua_Image = state.new_usertype<Image>("Image");
		lua_Image.set("new", sol::constructors<Image(void *, int, int, int, int)>());
		lua_Image.set("data", &Image::data);
		lua_Image.set("width", &Image::width);
		lua_Image.set("height", &Image::height);
		lua_Image.set("mipmaps", &Image::mipmaps);
		lua_Image.set("format", &Image::format);

		auto lua_Texture = state.new_usertype<Texture>("Texture");
		lua_Texture.set("new", sol::constructors<Texture(uint, int, int, int, int)>());
		lua_Texture.set("id", &Texture::id);
		lua_Texture.set("width", &Texture::width);
		lua_Texture.set("height", &Texture::height);
		lua_Texture.set("mipmaps", &Texture::mipmaps);
		lua_Texture.set("format", &Texture::format);

		auto lua_Camera = state.new_usertype<Camera>("Camera");
		lua_Camera.set("angle", &Camera::angle);
		lua_Camera.set("zoom", &Camera::zoom);
		lua_Camera.set("target", &Camera::target);
		lua_Camera.set("position", &Camera::position);
		lua_Camera.set("follow", &Camera::follow);
		lua_Camera.set("blend", &Camera::blend);
		lua_Camera.set("backgroundColor", &Camera::backgroundColor);
		lua_Camera.set("color", &Camera::color);
		lua_Camera.set("shaders", &Camera::shaders);
		lua_Camera.set("flash", &Camera::flash);
		lua_Camera.set("containsPoint", &Camera::containsPoint);
		lua_Camera.set("getScreenToWorld", &Camera::getScreenToWorld);
		lua_Camera.set("getWorldToScreen", &Camera::getWorldToScreen);
		lua_Camera.set("getCamera", &Camera::getCamera);
		lua_Camera.set("getCanvas", &Camera::getCanvas);

		auto lua_BlendMode = state.new_enum<BlendMode>("BlendMode", {BIND_ENUM(BLEND_ALPHA), BIND_ENUM(BLEND_ADDITIVE),
																	 BIND_ENUM(BLEND_MULTIPLIED), BIND_ENUM(BLEND_ADD_COLORS),
																	 BIND_ENUM(BLEND_SUBTRACT_COLORS), BIND_ENUM(BLEND_ALPHA_PREMULTIPLY),
																	 BIND_ENUM(BLEND_CUSTOM), BIND_ENUM(BLEND_CUSTOM_SEPARATE)});

		auto lua_ShaderUniformDataType = state.new_enum<ShaderUniformDataType>(
				"ShaderUniformDataType", {BIND_ENUM(SHADER_UNIFORM_FLOAT), BIND_ENUM(SHADER_UNIFORM_VEC2), BIND_ENUM(SHADER_UNIFORM_VEC3),
										  BIND_ENUM(SHADER_UNIFORM_VEC4), BIND_ENUM(SHADER_UNIFORM_INT), BIND_ENUM(SHADER_UNIFORM_IVEC2),
										  BIND_ENUM(SHADER_UNIFORM_IVEC3), BIND_ENUM(SHADER_UNIFORM_IVEC4), BIND_ENUM(SHADER_UNIFORM_UINT),
										  BIND_ENUM(SHADER_UNIFORM_UIVEC2), BIND_ENUM(SHADER_UNIFORM_UIVEC3),
										  BIND_ENUM(SHADER_UNIFORM_UIVEC4), BIND_ENUM(SHADER_UNIFORM_SAMPLER2D)});

		// funkin

		auto lua_Game = state.new_usertype<Game>("Game");
		lua_Game.set("defaultCamera", sol::var(std::ref(Game::defaultCamera)));

		auto lua_Sprite = bindSpriteSubclass<Sprite>(&state, "Sprite");
		lua_Sprite.set("new", [](float x, float y) { return std::make_shared<Sprite>(x, y); });

		auto lua_Character = bindSpriteSubclass<objects::Character>(&state, "Character");
		lua_Character.set("dancesLeftAndRight", &objects::Character::dancesLeftAndRight);
		lua_Character.set("danceEvery", &objects::Character::danceEvery);
		lua_Character.set("holdTimer", &objects::Character::holdTimer);
		lua_Character.set("singDuration", &objects::Character::singDuration);
		lua_Character.set("type", &objects::Character::type);
		lua_Character.set("barColor", &objects::Character::barColor);
		lua_Character.set("cameraOffset", &objects::Character::cameraOffset);

		auto lua_Stage = state.new_usertype<objects::Stage>("Stage");
		lua_Stage.set("stageName", &objects::Stage::stageName);
		lua_Stage.set("add", sol::overload(&objects::Stage::add<Sprite>, &objects::Stage::add<objects::Character>));
		lua_Stage.set("snapToPosition", &objects::Stage::snapToPosition);


		auto lua_AnimationController = state.new_usertype<game::AnimationController>("AnimationController");
		lua_AnimationController.set("new", sol::constructors<game::AnimationController(Sprite *)>());
		lua_AnimationController.set("isFinished", &game::AnimationController::isFinished);
		lua_AnimationController.set(
				"addByPrefix", sol::overload(
									   [](game::AnimationController &animationController, const std::string &name,
										  const std::string &prefix, const std::uint8_t framerate, const bool looped, sol::table indices) {
										   animationController.addByPrefix(name, prefix, framerate, looped,
																		   tableToVector<std::uint8_t>(std::move(indices)));
									   },
									   &game::AnimationController::addByPrefix));
		lua_AnimationController.set("addOffset", [](game::AnimationController &animationController, const std::string &name, const float x,
													const float y) { animationController.addOffset(name, x, y); });
		lua_AnimationController.set("loadSparrow", &game::AnimationController::loadSparrow);
		lua_AnimationController.set("play", sol::overload([](game::AnimationController &animationController,
															 const std::string &name) { animationController.play(name); },
														  [](game::AnimationController &animationController, const std::string &name,
															 const bool force) { animationController.play(name, force); }));


#define SHADER_SET(t)                                                                                                                      \
	[](const std::shared_ptr<graphics::Shader> &shader, const std::string &uniform, const t value,                                         \
	   const ShaderUniformDataType uniformType) { shader->setValue(uniform, value, uniformType); }

		auto lua_Shader = state.new_usertype<graphics::Shader>("Shader");

		lua_Shader.set("new", [](const std::string &fragmentPath) { return std::make_shared<graphics::Shader>(fragmentPath); });
		lua_Shader.set("setValue",
					   sol::overload(SHADER_SET(float), SHADER_SET(Vector2), SHADER_SET(Vector3), SHADER_SET(Vector4), SHADER_SET(Color)));

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
