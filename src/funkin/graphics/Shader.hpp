#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

namespace funkin::graphics {
	class Shader {
	public:
		explicit Shader(const std::string &fragmentPath);
		Shader(const std::string &fragmentPath, const std::string &vertexPath);
		~Shader();

		template<typename T>
		void setValue(const std::string &uniform, T value, const ShaderUniformDataType uniformType) {
			if (!locs.contains(uniform)) {
				locs[uniform] = GetShaderLocation(shader, uniform.c_str());
			}
			values[uniform] = static_cast<void *>(&value);
			SetShaderValue(shader, locs[uniform], values[uniform], uniformType);
		}

		::Shader getShader() const;

	private:
		std::unordered_map<std::string, int> locs = {};
		std::unordered_map<std::string, void *> values = {};
		::Shader shader{};
	};
} // namespace funkin::graphics
