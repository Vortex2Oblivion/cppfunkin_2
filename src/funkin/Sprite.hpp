#pragma once

#include <string>
#include <unordered_map>

#include "Object.hpp"

namespace funkin {
	class Sprite : public Object {
		public:
			explicit Sprite(float x = 0.0f, float y = 0.0f);
			~Sprite() override;

			Texture texture = {};
			Rectangle source = {};

			Vector2 scale = Vector2One();
			Vector2 origin = Vector2Zero();
			Color color = WHITE;
			float angle = 0.0f;
			float alpha = 1.0f;

			Rectangle hitbox = {};
			Color hitboxColor = BLUE;
			bool drawHitbox = false;

			void draw(float x, float y) override;
			bool loadTexture(const std::string& path);
		protected:
			static std::unordered_map<std::string, Texture> textureCache;
	};
} // funkin