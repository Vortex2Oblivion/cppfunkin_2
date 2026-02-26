#pragma once

#include <string>
#include <unordered_map>

#include "AnimationController.hpp"
#include "Object.hpp"

namespace funkin {
	class Sprite : public Object {
	public:
		explicit Sprite(float x = 0.0f, float y = 0.0f);

		~Sprite() override;

		bool drawHitbox = false;

		float angle = 0.0f;
		float alpha = 1.0f;

		Color color = WHITE;
		Color hitboxColor = BLUE;

		Vector2 origin = Vector2Zero();
		Vector2 offset = Vector2Zero();
		Vector2 scale = Vector2One();

		Rectangle source = {};
		Rectangle hitbox = {};

		Texture texture = {};

		game::AnimationController animation = game::AnimationController();

		bool loadTexture(const std::string &path);

		void updateHitbox();
		void centerOffsets();

		void draw(float x, float y) override;
		void update(float delta) override;

		void add();

	protected:
		static std::unordered_map<std::string, Texture> textureCache;
	};
} // funkin