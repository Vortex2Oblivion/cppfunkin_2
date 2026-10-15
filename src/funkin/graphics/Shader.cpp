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


	::Shader Shader::getShader() const { return shader; }
} // namespace funkin::graphics
