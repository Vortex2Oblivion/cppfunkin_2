#pragma once

#include "Object.hpp"

namespace funkin {
	class Sprite : public Object {
		public:
			Sprite(float x = 0.0f, float y = 0.0f);
			~Sprite() override;

			Texture texture;

			void draw(float x, float y) override;
	};
} // funkin