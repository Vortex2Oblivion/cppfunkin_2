#pragma once
#include "Group.hpp"

namespace funkin {
	class Scene : public Group<> {
		friend class Game;

		public:
			Scene();
			~Scene();

			bool& initialized = _initialized;
		protected:
			void create() const;

			bool _initialized = false;
	};
} // funkin