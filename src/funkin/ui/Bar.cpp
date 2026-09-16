
#include "Bar.hpp"

namespace funkin::ui {
	Bar::Bar(const float x, const float y, const int width, const int height, const Color colorLeft, const Color colorRight,
			 const Color outlineColor) : Sprite(x, y) {
		this->colorLeft = colorLeft;
		this->colorRight = colorRight;
		this->outlineColor = outlineColor;

		progressShader = std::make_shared<graphics::Shader>("assets/shaders/progressbar.fs");

		progressShader->setValue("progress", progress, SHADER_UNIFORM_FLOAT);
		progressShader->setValue("fillColor", ColorNormalize(colorLeft), SHADER_UNIFORM_VEC4);

		shaders.push_back(progressShader);

		makeTexture(width, height, colorRight);
	}

	Bar::~Bar() = default;

	float Bar::getMiddle() const { return position.x + dest.width * abs(1.0f - progress / 100.0f); }

	void Bar::update(const float delta) {
		Sprite::update(delta);

		const float _progress = fillDirection == FillDirection::LEFT_TO_RIGHT ? progress : 100.0f - progress;

		progressShader->setValue("progress", _progress, SHADER_UNIFORM_FLOAT);
		progressShader->setValue("fillColor", ColorNormalize(colorLeft), SHADER_UNIFORM_VEC4);
	}

	void Bar::draw(const float x, const float y, const std::shared_ptr<Camera> &cam) {
		DrawRectanglePro(Rectangle{.x = position.x + x - borderSize,
								   .y = position.y + y - borderSize,
								   .width = dest.width + borderSize * 2.0f,
								   .height = dest.height + borderSize * 2.0f},
						 origin, angle, outlineColor);
		Sprite::draw(x, y, cam);
	}
} // namespace funkin::ui
