#include "Shader.hpp"


namespace funkin::graphics {
	Shader::Shader(const std::filesystem::path &fragmentPath) { shader = LoadShader(nullptr, fragmentPath.string().c_str()); }

	Shader::Shader(const std::filesystem::path &fragmentPath, const std::filesystem::path &vertexPath) {
		shader = LoadShader(vertexPath.string().c_str(), fragmentPath.string().c_str());
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
