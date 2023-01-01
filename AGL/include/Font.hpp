#pragma once

#include "Texture.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace agl
{
	class Glyph
	{
		public:
			Vec<int, 2> size;
			Vec<int, 2> position;
	};

	class Font
	{
		private:
			FT_Face face;
			Glyph glyph[128];
			Vec<int, 2> atlasSize;
		public:
			Texture texture;
			void setup();
			Glyph getGlyph(int i);
	};
}
