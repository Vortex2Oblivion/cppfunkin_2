
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

		colorLeftNormalized = ColorNormalize(colorLeft);

		SetShaderValue(progressShader, progressLoc, &_progress, SHADER_UNIFORM_FLOAT);
		SetShaderValue(progressShader, fillColorLoc, &colorLeftNormalized, SHADER_UNIFORM_VEC4);

		makeTexture(width, height, colorRight);
	}

	Bar::~Bar() = default;

	void Bar::update(const float delta) {
		Sprite::update(delta);
		switch (fillDirection) {
			case FillDirection::LEFT_TO_RIGHT:
				_progress = progress;
				break;
			case FillDirection::RIGHT_TO_LEFT:
				_progress = 100 - progress;
				break;
		}
		SetShaderValue(progressShader, progressLoc, &_progress, SHADER_UNIFORM_FLOAT);
	}

	void Bar::draw(const float x, const float y, const std::shared_ptr<Camera> cam) {
		DrawRectanglePro((Rectangle) {.x = position.x + x - borderSize,
									  .y = position.y + y - borderSize,
									  .width = dest.width + borderSize * 2.0f,
									  .height = dest.height + borderSize * 2.0f},
						 origin, angle, outlineColor);
		BeginShaderMode(progressShader);
		Sprite::draw(x, y, cam);
		EndShaderMode();
	}
} // namespace funkin::ui
