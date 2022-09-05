#include "../include/GLPrimative.hpp"
#include <stdlib.h>
#include <GL/glew.h>
#include <stdio.h>

void agl::GLPrimative::setMode(int mode)
{
	this->mode = mode;

	return;
}

void agl::GLPrimative::setVertexData(float vertexBufferData[], int size)
{
	this->vertexDataSize = size;
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertexBufferData, GL_STATIC_DRAW);
	
	return;
}

void agl::GLPrimative::setColorData(float colorBufferData[], int size)
{
	this->colorDataSize = size;

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, colorBufferData, GL_STATIC_DRAW);

	return;
}

int agl::GLPrimative::getMode()
{
	return mode;
}

unsigned int agl::GLPrimative::getVertexBuffer()
{
	return vertexBuffer;
}

unsigned int agl::GLPrimative::getColorBuffer()
{
	return colorBuffer;
}

int agl::GLPrimative::getVertexDataSize()
{
	return vertexDataSize;
}

int agl::GLPrimative::getColorDataSize()
{
	return colorDataSize;
}

void agl::GLPrimative::deleteData()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);

	return;
}
