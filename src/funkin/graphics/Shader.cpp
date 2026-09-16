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
	}

	void Shader::setMatrixValue(const std::string &uniform, const Matrix &matrix) {
		if (!IsShaderValid(shader)) {
			TraceLog(LOG_ERROR, TextFormat("SHADER: could not set shader value %s, shader is invalid.", uniform.c_str()));
			return;
		}
		if (!locs.contains(uniform)) {
			locs[uniform] = GetShaderLocation(shader, uniform.c_str());
		}
		SetShaderValueMatrix(shader, locs[uniform], matrix);
	}

	::Shader Shader::getShader() const { return shader; }
} // namespace funkin::graphics
