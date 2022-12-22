#include "../include/Texture.hpp"
#include <SOIL/SOIL.h>
#include <cstdio>

int agl::Texture::loadFromFile(const char *filePath)
{
	// Create one OpenGL texture
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify
	// this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	int			   width, height;
	unsigned char *data = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGBA);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// free data
	SOIL_free_image_data(data);

	// Poor filtering, or ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering ...
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	// glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created

	return 0;
}

void agl::Texture::setBlank()
{
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned char data[] = {255, 255, 255};

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Poor filtering, or ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return;
}

void agl::Texture::bind(int textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void agl::Texture::deleteTexture()
{
	glDeleteTextures(1, &textureID);
}

unsigned int agl::Texture::getTextureID()
{
	return textureID;
}
