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

		glyph[i].size = {(int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows};

		width += face->glyph->bitmap.width;

		if (face->glyph->bitmap.rows > height)
		{
			height = face->glyph->bitmap.rows;
		}
	}

	int sideLength = 1;

	for (int i = 0; (sideLength * sideLength) < (width * height); i++)
	{
		sideLength *= 2;
	}

	atlasSize = {sideLength, sideLength};

	unsigned char *texData = new unsigned char[sideLength * sideLength * 4];

	Vec<int, 2> offset = {0, 0};

	for (int i = 33; i < 127; i++)
	{
		FT_Load_Char(face, i, FT_LOAD_RENDER);

		FT_Bitmap bitmap = face->glyph->bitmap;

		if (bitmap.width + offset.x > sideLength)
		{
			offset.x = 0;
			offset.y += height;
		}

		for (int x = 0; x < bitmap.width; x++)
		{
			for (int y = 0; y < bitmap.rows; y++)
			{
				int bufIndex = (y * bitmap.width) + x;
				int texIndex = ((y + offset.y) * sideLength * 4) + ((x + offset.x) * 4);

				texData[texIndex + 0] = 0;
				texData[texIndex + 1] = 0;
				texData[texIndex + 2] = 0;
				texData[texIndex + 3] = bitmap.buffer[bufIndex];
			}
		}

		glyph[i].size.x = bitmap.width;
		glyph[i].size.y = bitmap.rows;

		glyph[i].scale.x = (float)glyph[i].size.x / sideLength;
		glyph[i].scale.y = (float)glyph[i].size.y / sideLength;

		glyph[i].position.x = (float)offset.x / sideLength;
		glyph[i].position.y = (float)offset.y / sideLength;

		offset.x += bitmap.width;
	}

	FT_Done_FreeType(ft);

	texture.genTexture();
	Texture::bind(texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sideLength, sideLength, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	texture.useNearestFiltering();

	return;
}

void agl::Font::deleteFont()
{
	texture.deleteTexture();
}

agl::Texture *agl::Font::getTexture()
{
	return &texture;
}

agl::Glyph *agl::Font::getGlyph(int i)
{
	return &glyph[i];
}
