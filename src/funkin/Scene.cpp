#include "Scene.hpp"

namespace funkin {
	Scene::Scene() : Group(0, 0) {}

	Scene::~Scene() = default;

	void Scene::create() { initialized = true; }

	const char *Scene::getTypeName() {
		return typeid(this).name();
	}
} // namespace funkin
