#include "../include/Texture.hpp"
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include AGL_STB_IMAGE_INC

agl::Texture::Texture()
{
}

void agl::Texture::genTexture()
{
	glGenTextures(1, &textureID);
}

void agl::Texture::setImage(int format, int internalFormat, Vec<int, 2> size, unsigned char *data)
{
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);
}

void agl::Texture::setParameter(int pname, int parameter)
{
	glTexParameteri(GL_TEXTURE_2D, pname, parameter);
}

void agl::Texture::loadFromFile(const char *filePath)
{
	// generate
	this->genTexture();

	// bind
	Texture::bind(*this);

	// load image data
	//unsigned char *data = SOIL_load_image(filePath, &size.x, &size.y, 0, SOIL_LOAD_RGBA);
  unsigned char *data = stbi_load(filePath, &size.x, &size.y, 0, 4);
  if(!data)
  {
		printf("ERROR::FONT: Could not load image file: %s", filePath);
  }
	// set texture data
	Texture::setImage(GL_RGBA, GL_RGBA, size, data);

	// free data
	stbi_image_free(data);

	// set nearest filtering
	Texture::setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	Texture::setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return;
}

void agl::Texture::setBlank()
{
	// generate
	this->genTexture();

	// bind
	Texture::bind(*this);

	// set image data
	unsigned char data[] = {255, 255, 255, 255};
	size = {1, 1};
	
	// set texture data
	Texture::setImage(GL_RGBA, GL_RGBA, size, data);


	// set nearest filtering
	Texture::setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	Texture::setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return;
}

void agl::Texture::bind(Texture texture)
{
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
}

void agl::Texture::useNearestFiltering()
{
	Texture::bind(*this);

	Texture::setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	Texture::setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void agl::Texture::useLinearFiltering()
{
	Texture::bind(*this);

	Texture::setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Texture::setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void agl::Texture::deleteTexture()
{
	glDeleteTextures(1, &textureID);
}

unsigned int agl::Texture::getTextureID()
{
	return textureID;
}

agl::Vec<int, 2> agl::Texture::getSize()
{
	return size;
}
