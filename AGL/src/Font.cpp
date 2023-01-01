#include "../include/Font.hpp"
#include "freetype/freetype.h"
#include <cstdio>

void agl::Font::setup()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		printf("ERROR::FREETYPE: Could not init FreeType Library");
	}

	if (FT_New_Face(ft, "/usr/share/fonts/TTF/Arial.TTF", 0, &face))
	{
		printf("ERROR::FREETYPE: Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	int width  = 0;
	int height = 0;

	for (int i = 33; i < 127; i++)
	{
		FT_Load_Char(face, i, FT_LOAD_RENDER);

		glyph[i].size = {(int)face->glyph->bitmap.width, (int)face->glyph->bitmap.width};

		glyph[i].position = {width, 0};

		width += glyph[i].size.x;

		if (glyph[i].size.y > height)
		{
			height = glyph[i].size.y;
		}

		printf("%d %c %d\n", i, i, width);
	}

	printf("%d\n%d\n", width, height);

	int sideLength = 1;

	for (int i = 0; (sideLength * sideLength) < (width * height); i++)
	{
		sideLength *= 2;
	}

	atlasSize = {sideLength, sideLength};

	unsigned char *buffer = new unsigned char[sideLength * sideLength * 4];

	for (int i = 0; i < (sideLength * sideLength * 4); i++)
	{
		buffer[i] = 16;
	}

	Vec<int, 2> offset = {0, 0};

	for (int i = 33; i < 40; i++)
	{
		FT_Load_Char(face, 33, FT_LOAD_RENDER);
		
		FT_Bitmap bitmap = face->glyph->bitmap;

		for (int x = offset.x; x < (bitmap.width + offset.x); x++)
		{
			for (int y = offset.y; y < (bitmap.rows + offset.y); y++)
			{
				buffer[((y * sideLength * 4) + (x * 4)) + 0] = 88;
				buffer[((y * sideLength * 4) + (x * 4)) + 1] = 255;
				buffer[((y * sideLength * 4) + (x * 4)) + 2] = 255;
				buffer[((y * sideLength * 4) + (x * 4)) + 3] = 255;
			}
		}

		offset.x += width;
	}

	FT_Done_FreeType(ft);

	texture.genTexture();
	Texture::bind(texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sideLength, sideLength, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	texture.useNearestFiltering();

	return;
}

agl::Glyph agl::Font::getGlyph(int i)
{
	return glyph[i];
}
