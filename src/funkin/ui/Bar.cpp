
#include "Bar.hpp"

namespace funkin::ui {
	Bar::Bar(const float x, const float y, const int width, const int height, const Color colorLeft, const Color colorRight,
			 const Color outlineColor) : Sprite(x, y) {
		this->colorLeft = colorLeft;
		this->colorRight = colorRight;
		this->outlineColor = outlineColor;

		progressShader = LoadShader(nullptr, "assets/shaders/progressbar.fs");
		progressLoc = GetShaderLocation(progressShader, "progress");
		fillColorLoc = GetShaderLocation(progressShader, "fillColor");

		colorLeftPtr = static_cast<float *>(malloc(3 * sizeof(float)));
		colorLeftPtr[0] = colorLeft.r / 255.0f;
		colorLeftPtr[1] = colorLeft.g / 255.0f;
		colorLeftPtr[2] = colorLeft.b / 255.0f;

		SetShaderValue(progressShader, progressLoc, &progress, SHADER_UNIFORM_FLOAT);
		SetShaderValue(progressShader, fillColorLoc, colorLeftPtr, SHADER_UNIFORM_VEC3);

		/*outlineShader = LoadShader(nullptr, "assets/shaders/outline.fs");
		outlineSizeLoc = GetShaderLocation(outlineShader, "outlineSize");
		outlineColorLoc = GetShaderLocation(outlineShader, "outlineColor");
		textureSizeLoc = GetShaderLocation(outlineShader, "textureSize");

		outlineColorPtr = static_cast<float *>(malloc(4 * sizeof(float)));
		outlineColorPtr[0] = outlineColor.r / 255.0f;
		outlineColorPtr[1] = outlineColor.g / 255.0f;
		outlineColorPtr[2] = outlineColor.b / 255.0f;
		outlineColorPtr[4] = outlineColor.a / 255.0f;

		textureSize = static_cast<float *>(malloc(2 * sizeof(float)));
		textureSize[0] = width;
		textureSize[1] = height;

		SetShaderValue(outlineShader, outlineSizeLoc, &borderSize, SHADER_UNIFORM_FLOAT);
		SetShaderValue(outlineShader, outlineColorLoc, outlineColorPtr, SHADER_UNIFORM_VEC4);
		SetShaderValue(outlineShader, textureSizeLoc, textureSize, SHADER_UNIFORM_VEC2);*/

		makeTexture(width, height, colorRight);
	}

	Bar::~Bar() { free(colorLeftPtr); }

	void Bar::update(const float delta) {
		Sprite::update(delta);
		SetShaderValue(progressShader, progressLoc, &progress, SHADER_UNIFORM_FLOAT);
	}

	void Bar::draw(const float x, const float y, const std::shared_ptr<Camera> cam) {
		BeginShaderMode(progressShader);
		Sprite::draw(x, y, cam);
		EndShaderMode();

	}
} // namespace funkin::ui
