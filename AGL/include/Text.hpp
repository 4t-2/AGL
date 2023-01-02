#pragma once

#include "Font.hpp"
#include "Rectangle.hpp"
#include "Texture.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace agl
{
	class Text
	{
		private:
			agl::Rectangle charBox;
			agl::Glyph	 **glyph  = nullptr;
			agl::Font	  *font	  = nullptr;
			int			   length = 0;

		public:
			void setFont(Font *font);
			void setText(char *str, int length);

			void clearText();

			Glyph		   *getGlyph(int i);
			agl::Rectangle *getCharBox();
			int				getLength();
			Font		   *getFont();
	};
} // namespace agl
