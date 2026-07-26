#pragma once
#include "Sprite.hpp"

namespace funkin {
	class Text : public Sprite {
	public:
		static std::unordered_map<std::string, Font> fontCache;
		Text(float x, float y, const std::string &text);
		~Text() override;

		float size = 24.0f;
		float spacing = 1.0f;
		float borderSize = 0.0f;

		Color borderColor = BLACK;

		void loadFont(const std::string &path);
		std::string getText();
		void setText(const std::string &newText);

		void updateHitbox() override;
		void draw(float x, float y, const std::shared_ptr<Camera> &cam) override;

		static void clearFontCache();

	protected:
		std::string text;
		Font font = GetFontDefault();
		static std::unordered_map<std::string, Texture> textureCache;
	};
} // namespace funkin
