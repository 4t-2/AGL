#include "../include/GLPrimative.hpp"
#include <stdio.h>
#include <stdlib.h>

void agl::GLPrimative::setMode(int mode)
{
	this->mode = mode;

	return;
}

void agl::GLPrimative::genBuffers(int amount)
{	
	bufferAmount = amount;
	buffer = (unsigned int *)malloc(bufferAmount * sizeof(unsigned int *));
	vertexSize = (int *)malloc(bufferAmount * sizeof(int *));

	for(int i = 0; i < bufferAmount; i++)
	{
		glGenBuffers(1, &buffer[i]);
	}

	return;
}

void agl::GLPrimative::setVertexAmount(int amount)
{
	vertexAmount = amount;

	return;
}

void agl::GLPrimative::setBufferData(int index, float bufferData[], int vertexSize)
{
	this->vertexSize[index] = vertexSize;

	glBindBuffer(GL_ARRAY_BUFFER, buffer[index]);
	glBufferData(GL_ARRAY_BUFFER, vertexAmount * this->vertexSize[index] * 4, bufferData, GL_STATIC_DRAW);

	return;
}

int agl::GLPrimative::getBufferAmount()
{
	return bufferAmount;
}

int agl::GLPrimative::getVertexAmount()
{
	return vertexAmount;
}

int agl::GLPrimative::getVertexSize(int index)
{
	return vertexSize[index];
}

unsigned int agl::GLPrimative::getBuffer(int index)
{
	return buffer[index];
}

int agl::GLPrimative::getMode()
{
	return mode;
}

void agl::GLPrimative::deleteData()
{
	for(int i = 0; i < bufferAmount; i++)
	{
		glDeleteBuffers(1, &buffer[i]);
	}

	free(buffer);
	free(vertexSize);

	return;
}
