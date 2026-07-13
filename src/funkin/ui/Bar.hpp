#pragma once
#include "funkin/Sprite.hpp"

namespace funkin::ui {
	class Bar : public Sprite {
	public:
		Bar(float x, float y, int width, int height, Color colorLeft, Color colorRight, Color outlineColor = BLANK);
		~Bar() override;

		float borderSize = 8.0f;
		float progress = 0.5f;
		Color colorLeft = BLANK;
		Color colorRight = BLANK;
		Color outlineColor = BLANK;

		void draw(float x, float y, std::shared_ptr<Camera> cam) override;
		void update(float delta) override;

	protected:
		int fillColorLoc = 0;
		int progressLoc = 0;
		float *colorLeftPtr;
		Shader progressShader{};

		/*int outlineSizeLoc = 0;
		int outlineColorLoc = 0;
		int textureSizeLoc = 0;
		float *outlineColorPtr;
		float *textureSize;
		Shader outlineShader{};*/
	};
} // namespace funkin::ui
