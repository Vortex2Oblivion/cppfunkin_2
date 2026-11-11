#pragma once

#include "funkin/utilities/CoolUtil.hpp"
#include "raylib.h"
#include "raymath.h"

namespace funkin::data::animation {
	struct Frame {
		Rectangle source;
		Rectangle dest;
		std::string name;
		bool rotated;

		void prepareMatrix(Matrix &matrix, const float angle, const bool flipX, const bool flipY) const {
			// TODO: fix rotated and flipped matrix
			auto [x, y] = Vector2Rotate(Vector2{.x = dest.x, .y = dest.y}, angle * DEG2RAD);
			float w = x;
			float h = y;

			if (rotated) {
				std::swap(w, h);

				matrix *= MatrixRotateZ(-PI / 2.0f);
				matrix *= MatrixTranslate(0.0f, dest.height - y, 0.0f);
			}

			if (flipX) {
				matrix *= MatrixScale(-1.0f, 1.0f, 1.0f);
				matrix *= MatrixTranslate(-w * 2.0f, 0.0, 0.0f);
			}

			if (flipY) {
				matrix *= MatrixScale(1.0f, -1.0f, 1.0f);
				matrix *= MatrixTranslate(0.0f, -h * 2.0f, 0.0f);
			}
		}
	};

} // namespace funkin::data::animation
