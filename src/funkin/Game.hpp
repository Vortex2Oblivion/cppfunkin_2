#pragma once

#include "Group.hpp"

namespace funkin {
	class Game {
		public:
			static Group<> scene;
			static void Start(const Group<>& initialScene);
	};
}
