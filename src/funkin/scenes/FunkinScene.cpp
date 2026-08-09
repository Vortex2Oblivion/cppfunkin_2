#include "FunkinScene.hpp"
#include "eventpp/callbacklist.h"

namespace funkin::scenes {
	std::shared_ptr<game::Conductor> FunkinScene::conductor = std::make_shared<game::Conductor>();

	FunkinScene::FunkinScene() = default;
	FunkinScene::~FunkinScene() {
		conductor->onBeatHit = eventpp::CallbackList<void(std::uint16_t)>();
		conductor->onStepHit = eventpp::CallbackList<void(std::uint16_t)>();
	};

	void FunkinScene::update(const float delta) {
		Scene::update(delta);
		if (conductor != nullptr) {
			conductor->update(delta);
		}
	}
} // namespace funkin::scenes
