#pragma once

#include "Texture.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace agl
{
	class Glyph
	{
		public:
			Vec<int, 2>	  size;		// pixels
			Vec<float, 2> scale;	// fraction of texture
			Vec<float, 2> position; // fraction of texture
	};

	class Font
	{
		private:
			FT_Face		face;
			Glyph		glyph[128];
			Vec<int, 2> atlasSize;
			Texture texture;

		public:
			void	setup();
			
			void deleteFont();
			
			Texture *getTexture();
			Glyph	*getGlyph(int i);
	};
} // namespace agl
