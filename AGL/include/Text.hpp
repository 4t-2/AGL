#pragma once

#include "Color.hpp"
#include "Font.hpp"
#include "Rectangle.hpp"
#include "Texture.hpp"

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace agl
{
	class Text
	{
		private:
			agl::Rectangle	   charBox;
			agl::Glyph		 **glyph  = nullptr;
			agl::Font		  *font	  = nullptr;
			int				   length = 0;
			int				   height = 0;
			agl::Vec<float, 3> position;
			float			   scale = 0;
			float			   width = 0; // unscaled

		public:
			void setFont(Font *font);
			void setText(std::string str);
			void setScale(float scale);
			void setPosition(agl::Vec<float, 3> position);
			void setColor(agl::Color color);

			void clearText();

			Glyph			  *getGlyph(int i);
			agl::Rectangle	  *getCharBox();
			int				   getLength();
			Font			  *getFont();
			int				   getHeight();
			agl::Vec<float, 3> getPosition();
			float			   getScale();
			float			   getWidth();
	};
} // namespace agl
