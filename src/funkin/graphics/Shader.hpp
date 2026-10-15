#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include "raylib.h"

namespace funkin::graphics {
	class Shader {
	public:
		explicit Shader(const std::filesystem::path &fragmentPath);
		Shader(const std::filesystem::path &fragmentPath, const std::filesystem::path &vertexPath);
		~Shader();

		template<typename T>
		void setValue(const std::string &uniform, T value, const ShaderUniformDataType uniformType) {
			if (!IsShaderValid(shader)) {
				TraceLog(LOG_ERROR, TextFormat("SHADER: could not set shader value %s, shader is invalid.", uniform.c_str()));
				return;
			}

			if (!locs.contains(uniform)) {
				locs[uniform] = GetShaderLocation(shader, uniform.c_str());
			}

			if constexpr (std::is_same_v<T, Matrix>) {
				SetShaderValueMatrix(shader, locs[uniform], value);
			} else {
				values[uniform] = static_cast<void *>(&value);
				SetShaderValue(shader, locs[uniform], values[uniform], uniformType);
			}
		}

		::Shader getShader() const;

	private:
		std::unordered_map<std::string, int> locs = {};
		std::unordered_map<std::string, void *> values = {};
		::Shader shader{};
	};
} // namespace funkin::graphics
