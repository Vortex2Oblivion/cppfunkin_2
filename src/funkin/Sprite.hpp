#pragma once

#include "Object.hpp"

namespace funkin {
	class Sprite : public Object {
		public:
			Sprite(float x, float y);
			~Sprite() override;

			Texture& texture = _texture;

			void draw(float x, float y) override;
		protected:
			Texture _texture{};
	};
} // funkin