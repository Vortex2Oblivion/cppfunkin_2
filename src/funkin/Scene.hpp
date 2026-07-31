#pragma once
#include "Group.hpp"

namespace funkin {
	class Scene : public Group<> {
		friend class Game;
	public:
		Scene();
		~Scene() override;

		bool initialized = false;
		Color backgroundColor = BLACK;

		const char* getTypeName();

	protected:
		virtual void create();
	};
} // namespace funkin
