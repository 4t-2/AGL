#include "../include/GLPrimative.hpp"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

void agl::GLPrimative::setMode(int mode)
{
	this->mode = mode;

	return;
}

void agl::GLPrimative::genVertexBuffer()
{
	glGenBuffers(1, &vertexBuffer);

	return;
}

void agl::GLPrimative::genColorBuffer()
{
	glGenBuffers(1, &colorBuffer);

	return;
}

void agl::GLPrimative::setBufferSize(int size)
{
	bufferSize = size;

	return;
}

void agl::GLPrimative::setVertexData(float vertexBufferData[])
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexBufferData, GL_STATIC_DRAW);

	return;
}

void agl::GLPrimative::setColorData(float colorBufferData[])
{
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, colorBufferData, GL_STATIC_DRAW);

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

int agl::GLPrimative::getBufferSize()
{
	return bufferSize;
}

void agl::GLPrimative::deleteData()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);

	return;
}
