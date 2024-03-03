#include "../include/Font.hpp"
//#include "freetype/freetype.h"
#include <cstdio>
#include <iostream>

#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "stb_truetype.h"

#define MIN 32
#define MAX 127

void agl::Font::setup(const std::string &path, int height)
{
  static unsigned char filedata[100 * 1024];
  FILE* fontfile=0;
  
  if(fopen_s(&fontfile, path.c_str(), "rb"))
  {
		printf("ERROR::FONT: Could not load font file: %s", path.c_str());
    
  }
  fread(filedata, 1, 100*1024, fontfile);
	fclose(fontfile);

	this->height = height;

	//FT_Set_Pixel_Sizes(face, 0, height);
  /* prepare font */

  if (!stbtt_InitFont(&fontInfo, filedata, 0))
  {
      printf("ERROR::FONT: Could not read font file: %s", path.c_str());
  }
	int width  = 0;
  float scale = stbtt_ScaleForPixelHeight(&fontInfo, height);
  
  int ascent, descent, linegap;
  stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &linegap);
  ascent  = ascent  * scale;
  descent = descent * scale;
  linegap = linegap * scale;
  
	for(int i = 0; i < MIN; i++)
	{
		glyph[i].value = i;
	}

	for (int i = MIN; i < MAX; i++)
	{
		//FT_Load_Char(face, i, FT_LOAD_RENDER);
    int advance;
    int leftBearing;
    stbtt_GetCodepointHMetrics(&fontInfo, i, &advance, &leftBearing);
    int x0; 
    int y0;
    int x1;
    int y1;
    stbtt_GetCodepointBox(&fontInfo, i, &x0, &y0, &x1, &y1);
		glyph[i].size = {x1-x0, y1-y0};

		glyph[i].advance = advance*scale;//face->glyph->advance.x / 64;
		glyph[i].bearing = {leftBearing, ascent};
		glyph[i].value = i;

		width += x1-x0;//face->glyph->bitmap.width;
	}
  width = width*scale;
	int sideLength = 1;

	while ( (sideLength * sideLength) < (width * height))
	{
		sideLength *= 2;
	}

	atlasSize = {sideLength, sideLength};

	unsigned char *bitmap = new unsigned char[sideLength * sideLength];
unsigned int *texData = new unsigned int[sideLength * sideLength];


  stbtt_BakeFontBitmap(filedata, 0, height, bitmap, sideLength, sideLength, MIN, MAX-MIN, cdata);
  
  for(int i = 0; i < sideLength * sideLength; i++)
  {
    texData[i] = (bitmap[i]<<24)+
                 0xffffff;
                 // bitmap[i]<<16+
                 // bitmap[i]<<8+
                 // bitmap[i]<<0;
  }

	//Vec<int, 2> offset = {0, 0};

	for (int i = MIN; i < MAX; i++)
	{
		// FT_Load_Char(face, i, FT_LOAD_RENDER);

		// FT_Bitmap bitmap = face->glyph->bitmap;

		// if (bitmap.width + offset.x > sideLength)
		// {
			// offset.x = 0;
			// offset.y += height;
		// }

		// for (int x = 0; x < bitmap.width; x++)
		// {
			// for (int y = 0; y < bitmap.rows; y++)
			// {
				// int bufIndex = (y * bitmap.width) + x;
				// int texIndex = ((y + offset.y) * sideLength * 4) + ((x + offset.x) * 4);

				// texData[texIndex + 0] = bitmap.buffer[bufIndex];
				// texData[texIndex + 1] = bitmap.buffer[bufIndex];
				// texData[texIndex + 2] = bitmap.buffer[bufIndex];
				// texData[texIndex + 3] = bitmap.buffer[bufIndex];
			// }
		// }
    stbtt_aligned_quad stbchar;
    float x=0, y=0;
    stbtt_GetBakedQuad(cdata, sideLength, sideLength, i-MIN, &x, &y, &stbchar, true);
		glyph[i].size.x = (stbchar.x1-stbchar.x0);//bitmap.width;
		glyph[i].size.y = (stbchar.y1-stbchar.y0);//bitmap.rows;

		glyph[i].scale.x = (stbchar.s1-stbchar.s0);
		glyph[i].scale.y = (stbchar.t1-stbchar.t0);
    

		glyph[i].position.x = stbchar.s0 ;
		glyph[i].position.y = stbchar.t0 ;
    
   
		
    glyph[i].bearing.x =0;//stbchar.x0;
    glyph[i].bearing.y =-stbchar.y0;//-ascent;
    
    
    int advance;
    int leftBearing;
    stbtt_GetCodepointHMetrics(&fontInfo, i, &advance, &leftBearing);
    
    Glyph* g= &glyph[i];
    printf("add glyph: value =%c\n", (char)i);
    printf("         : bearing=%d, %d, \t advance =%d, from ttf = %d\n", g->bearing.x, g->bearing.y, g->advance, advance);
    //printf("         : advance =%d\n", g->advance);

    //Glyph* g= &glyph[i];
    // printf("add glyph: value =%c\n", (char)i);
    // printf("         : size=%d, %d\n", g->size.x, g->size.y);
    // printf("         : scale=%f, %f\n", g->scale.x, g->scale.y);
    // printf("         : pos=%f, %f\n", g->position.x, g->position.y);
    // printf("         : bearing=%d, %d\n", g->bearing.x, g->bearing.y);

		//offset.x += bitmap.width;
	}

	//FT_Done_FreeType(ft);
  

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
