#pragma once

#include <string>
#include <unordered_map>

#include "Object.hpp"
#include "game/AnimationController.hpp"
#include "math/Axes.hpp"

namespace funkin {
	class Sprite : public Object {
	public:
		explicit Sprite(float x = 0.0f, float y = 0.0f);

		~Sprite() override;

		bool drawHitbox = false;
	protected:
		bool antialiasing = true;
	public:

		float angle = 0.0f;
		float alpha = 1.0f;

		Color color = WHITE;
		Color hitboxColor = BLUE;

		Vector2 origin = Vector2Zero();
		Vector2 offset = Vector2Zero();
		Vector2 scale = Vector2One();
		Vector2 scrollFactor = Vector2One();

		Rectangle source = {};
		Rectangle dest = {};
		Rectangle hitbox = {};

		Texture texture = {};

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
		void centerOn(const std::shared_ptr<Sprite>& sprite, math::Axes axes = math::Axes::XY);

		void draw(float x, float y, std::shared_ptr<Camera> cam) override;
		void update(float delta) override;

		void setAntialiasing(bool enable) const;
		bool getAntialiasing() const;

		static void clearTextureCache();

	protected:
		static std::unordered_map<std::string, Texture> textureCache;
	};
} // funkin