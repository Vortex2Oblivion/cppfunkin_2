#pragma once
#include "raylib.h"

namespace funkin::data::animation {
	struct Frame : Rectangle {
		float x;
		float y;
		float width;
		float height;
		Vector2 offset;
		Vector2 sourceSize;
	};
}
