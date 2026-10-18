#pragma once

#include "raylib.h"
#include "raymath.h"

namespace funkin::data::animation {
	struct Frame {
		Rectangle source;
		Rectangle dest;
		std::string name;
		bool rotated;

		void prepareMatrix(Matrix &matrix, const bool flipX, const bool flipY) const {
			float w = dest.x;
			float h = dest.y;

			if (rotated) {
				const float t = w;
				w = h;
				h = t;

				matrix = MatrixMultiply(matrix, MatrixRotateZ(-PI / 2.0f));
				matrix = MatrixMultiply(matrix, MatrixTranslate(0.0f, dest.x, 0.0f));
			}

			if (flipX) {
				matrix = MatrixMultiply(matrix, MatrixScale(-1.0f, 1.0f, 1.0f));
				matrix = MatrixMultiply(matrix, MatrixTranslate(w, 0.0, 0.0f));
			}

			if (flipY) {
				matrix = MatrixMultiply(matrix, MatrixScale(1.0f, -1.0f, 1.0f));
				matrix = MatrixMultiply(matrix, MatrixTranslate(0.0f, h, 0.0f));
			}
		}
	};

} // namespace funkin::data::animation
