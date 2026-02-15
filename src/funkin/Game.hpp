#pragma once

#include "Group.hpp"

namespace funkin {
	class Game final {
		public:
			static void start(const Group<> &initialScene);

			static Group<>& scene;
		private:
			static Group<> _scene;
	};
}
