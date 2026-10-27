#pragma once

#include <string>
#include <unordered_map>

#include "Camera.hpp"
#include "game/AnimationController.hpp"
#include "graphics/Shader.hpp"
#include "math/Axes.hpp"

namespace funkin {
	class Sprite {
	public:
		explicit Sprite(float x = 0.0f, float y = 0.0f);
		virtual ~Sprite();

		bool drawHitbox = false;

		bool flipX = false;
		bool flipY = false;

		bool visible = true;

		float angle = 0.0f;
		float alpha = 1.0f;

		BlendMode blend = BLEND_ALPHA;

		bool alive = false;

		size_t ID = 0;
		Vector2 position = Vector2Zero();

		std::shared_ptr<Camera> camera = nullptr;

		Color color = WHITE;
		Color hitboxColor = BLUE;

		Vector2 origin = Vector2Zero();
		Vector2 offset = Vector2Zero();
		Vector2 scale = Vector2One();
		Vector2 scrollFactor = Vector2One();

		Vector2 velocity = Vector2Zero();
		Vector2 acceleration = Vector2Zero();
		Vector2 drag = Vector2Zero();
		Vector2 maxVelocity = Vector2{.x = 10000.0f, .y = 10000.0f};

		Matrix matrix = MatrixIdentity();

		float angularVelocity = 0.0f;
		float angularAcceleration = 0.0f;
		float angularDrag = 0.0f;
		float maxAngular = 0.0f;

		Rectangle source = {};
		Rectangle dest = {};
		Rectangle hitbox = {};

		Texture texture = {};

		std::vector<std::shared_ptr<graphics::Shader>> shaders = {};

		game::AnimationController animation;

		bool loadTexture(const std::string &path);
		void makeTexture(int width, int height, Color textureColor);
		bool isOnScreen(const std::shared_ptr<Camera> &cam) const;
		Vector2 getMidpoint() const;

		std::shared_ptr<data::animation::Animation> getCurrentAnimation() const;

		virtual void updateHitbox();
		void centerOffsets();
		void centerOrigin();
		void screenCenter(math::Axes axes = math::Axes::XY);
		void centerOn(Rectangle rect, math::Axes axes = math::Axes::XY);
		void centerOn(const std::shared_ptr<Sprite> &sprite, math::Axes axes = math::Axes::XY);

		virtual void draw(float x, float y, const std::shared_ptr<Camera> &cam);
		virtual void update(float delta);

		void setTextureWrap(TextureWrap wrap);
		TextureWrap getTextureWrap() const;

		void setAntialiasing(bool enable);
		bool getAntialiasing() const;

		static void clearTextureCache();
		static void precacheTexture(const std::string &path);

		static size_t getEstimatedVRAMUsage();

	protected:
		bool antialiasing = true;
		TextureWrap textureWrap = TEXTURE_WRAP_CLAMP;
		Vector2 rawPos = Vector2Zero();
		void updateMotion(float delta);
		void prepareMatrix();
		static std::unordered_map<std::string, Texture> textureCache;
	};
} // namespace funkin
