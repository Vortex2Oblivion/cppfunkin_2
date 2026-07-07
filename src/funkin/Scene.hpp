#pragma once
#include "Group.hpp"

namespace funkin {
	class Scene : public Group<> {
		friend class Game;

	public:
		Scene();

		~Scene() override;

		void draw(float x, float y, std::shared_ptr<Camera> cam) override;

		bool initialized = false;

		Color backgroundColor = BLACK;

	protected:
		virtual void create();
	};
} // funkin