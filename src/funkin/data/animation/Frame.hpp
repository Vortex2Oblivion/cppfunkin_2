#pragma once
#include "raylib.h"

namespace funkin::data::animation {
	struct Frame : Rectangle {
		Rectangle source;
		Vector2 offset;
		Vector2 sourceSize;
	};
}
