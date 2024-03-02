#pragma once

#include "Texture.hpp"
//#include <ft2build.h>
//#include FT_FREETYPE_H
#include "stb_truetype.h"

namespace agl
{
	class Glyph
	{
		public:
			char		  value;
			Vec<int, 2>	  size;		// pixels
			Vec<float, 2> scale;	// fraction of texture
			Vec<float, 2> position; // fraction of texture
			int			  advance;
			Vec<int, 2>	  bearing;
	};

	class Font
	{
		private:
			//FT_Face		face;
			Glyph		glyph[128];
			Vec<int, 2> atlasSize;
			Texture		texture;
			int			height;
      stbtt_fontinfo fontInfo;
      stbtt_bakedchar cdata[96];
      
		public:
			void setup(const std::string &path, int height);

			void deleteFont();

			Texture *getTexture();
			Glyph	*getGlyph(int i);
			int		 getHeight();
	};
} // namespace agl
