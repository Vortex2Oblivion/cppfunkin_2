#include "Scene.hpp"

namespace funkin {
	Scene::Scene() : Group(0, 0){

	}

	Scene::~Scene() = default;

	void Scene::create() const {
		initialized = true;
	}
} // funkin