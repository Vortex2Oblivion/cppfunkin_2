#include "FunkinScene.hpp"

namespace funkin::scenes {
	std::shared_ptr<game::Conductor> FunkinScene::conductor = std::make_shared<game::Conductor>();

	FunkinScene::FunkinScene() = default;
	FunkinScene::~FunkinScene() = default;

	void FunkinScene::update(const float delta) {
		Scene::update(delta);
		if (conductor != nullptr) {
			conductor->update(delta);
		}
	}
} // namespace funkin::scenes
