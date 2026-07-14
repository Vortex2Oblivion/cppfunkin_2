#pragma once
#include "funkin/Sprite.hpp"

namespace funkin::ui {
	enum class FillDirection {
		RIGHT_TO_LEFT,
		LEFT_TO_RIGHT
	};
	class Bar : public Sprite {
	public:
		Bar(float x, float y, int width, int height, Color colorLeft, Color colorRight, Color outlineColor = BLANK);
		~Bar() override;

		float borderSize = 8.0f;
		float progress = 50.0f;
		Color colorLeft = BLANK;
		Color colorRight = BLANK;
		Color outlineColor = BLANK;
		FillDirection fillDirection = FillDirection::LEFT_TO_RIGHT;

		void draw(float x, float y, std::shared_ptr<Camera> cam) override;
		void update(float delta) override;

	protected:
		float _progress = 50.0f;
		int fillColorLoc = 0;
		int progressLoc = 0;
		Vector4 colorLeftNormalized = Vector4Zero();
		Shader progressShader{};
	};
} // namespace funkin::ui
