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
			auto [x, y] = utilities::CoolUtil::fastRotateVec2(Vector2{.x = dest.x, .y = dest.y}, angle * DEG2RAD);
			float w = x;
			float h = y;

			if (rotated) {
				const float t = w;
				w = h;
				h = t;

				matrix = MatrixMultiply(matrix, MatrixRotateZ(-PI / 2.0f));
				matrix = MatrixMultiply(matrix, MatrixTranslate(0.0f, dest.height - y, 0.0f));
			}

			if (flipX) {
				matrix = MatrixMultiply(matrix, MatrixScale(-1.0f, 1.0f, 1.0f));
				matrix = MatrixMultiply(matrix, MatrixTranslate(-w * 2.0f, 0.0, 0.0f));
			}

			if (flipY) {
				matrix = MatrixMultiply(matrix, MatrixScale(1.0f, -1.0f, 1.0f));
				matrix = MatrixMultiply(matrix, MatrixTranslate(0.0f, h, 0.0f));
			}
		}
	};

} // namespace funkin::data::animation
