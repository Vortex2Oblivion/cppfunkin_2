#pragma once
#include "Sprite.hpp"

namespace funkin {
	class Text : public Sprite {
	public:
		static std::unordered_map<std::string, Font> fontCache;
		Text(float x, float y, const std::string &text);
		~Text() override;

		float size = 32.0f;
		float spacing = 1.0f;
		std::string text;

		void loadFont(const std::string &path);
		void draw(float x, float y, std::shared_ptr<Camera> cam) override;

	protected:
		Font _font = GetFontDefault();
		static std::unordered_map<std::string, Texture> textureCache;
	};
} // namespace funkin
