#pragma once
#include "Group.hpp"

namespace funkin {
	class Scene : public Group<> {
		friend class Game;

		public:
			Scene();
			~Scene() override;

			void draw(float x = 0.0f, float y = 0.0f) override;

			bool initialized = false;
		protected:
			virtual void create();
	};
} // funkin