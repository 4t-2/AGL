#include "../include/Font.hpp"
#include "freetype/freetype.h"
#include <cstdio>
#include <iostream>

#define MIN 32
#define MAX 127

void agl::Font::setup(std::string path, int height)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		printf("ERROR::FREETYPE: Could not init FreeType Library");
	}

	if (FT_New_Face(ft, path.c_str(), 0, &face))
	{
		printf("ERROR::FREETYPE: Failed to load font");
	}

	this->height = height;

	FT_Set_Pixel_Sizes(face, 0, height);

	int width  = 0;

	for(int i = 0; i < MIN; i++)
	{
		glyph[i].value = i;
	}

	for (int i = MIN; i < MAX; i++)
	{
		FT_Load_Char(face, i, FT_LOAD_RENDER);

		glyph[i].size = {(int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows};

		glyph[i].advance = face->glyph->advance.x / 64;
		glyph[i].bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top};
		glyph[i].value = i;

		width += face->glyph->bitmap.width;
	}

	int sideLength = 1;

	for (int i = 0; (sideLength * sideLength) < (width * height); i++)
	{
		sideLength *= 2;
	}

	atlasSize = {sideLength, sideLength};

	unsigned char *texData = new unsigned char[sideLength * sideLength * 4];

	Vec<int, 2> offset = {0, 0};

	for (int i = MIN; i < MAX; i++)
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

				texData[texIndex + 0] = bitmap.buffer[bufIndex];
				texData[texIndex + 1] = bitmap.buffer[bufIndex];
				texData[texIndex + 2] = bitmap.buffer[bufIndex];
				texData[texIndex + 3] = bitmap.buffer[bufIndex];
			}
		}

		glyph[i].size.x = bitmap.width;
		glyph[i].size.y = bitmap.rows;

		glyph[i].scale.x = (float)glyph[i].size.x / sideLength;
		glyph[i].scale.y = (float)glyph[i].size.y / sideLength;

		glyph[i].position.x = (float)offset.x / sideLength;
		glyph[i].position.y = (float)offset.y / sideLength;

		std::cout << 		glyph[i].position.x << '\n';

		offset.x += bitmap.width;
	}

	std::cout << sideLength << '\n';

	FT_Done_FreeType(ft);

	texture.genTexture();
	Texture::bind(texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sideLength, sideLength, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	texture.useNearestFiltering();

	delete[] texData;

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

int agl::Font::getHeight()
{
	return height;
}
