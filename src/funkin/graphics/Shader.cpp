#include "Shader.hpp"

#include <iostream>

namespace funkin::graphics {
	Shader::Shader(const std::string &fragmentPath) { shader = LoadShader(nullptr, fragmentPath.c_str()); }

	Shader::Shader(const std::string &fragmentPath, const std::string &vertexPath) {
		shader = LoadShader(vertexPath.c_str(), fragmentPath.c_str());
	}

	Shader::~Shader() {
		if (!WindowShouldClose()) {
			UnloadShader(shader);
		}
	};

	::Shader Shader::getShader() const { return shader; }
} // namespace funkin::graphics
