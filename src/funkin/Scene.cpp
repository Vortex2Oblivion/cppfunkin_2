#include "Scene.hpp"

namespace funkin {
	Scene::Scene() : Group(0, 0) {}

	Scene::~Scene() = default;

	void Scene::create() {
		initialized = true;
	}

	void Scene::draw(const float x, const float y) {
		Group::draw(x, y);
	}
} // funkin