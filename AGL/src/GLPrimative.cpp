#include "../include/GLPrimative.hpp"
#include <stdlib.h>
#include <GL/glew.h>
#include <stdio.h>

void g1enVertexBuffer(GLuint *vertexBuffer, GLfloat *vertexBufferData, int size)
{
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, vertexBuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, vertexBufferData, GL_STATIC_DRAW);
	return;
}

void agl::GLPrimative::setMode(int mode)
{
	this->mode = mode;

	return;
}

void agl::GLPrimative::setVertices(agl::Vector3f *vertex, int size)
{
	float *vertexBufferData = (float *)malloc(size);

	int x = (size / sizeof(*vertex));

	for (int i = 0; i < x; i++)
	{
		vertexBufferData[(i * 3)]	  = vertex[i].x;
		vertexBufferData[(i * 3) + 1] = vertex[i].y;
		vertexBufferData[(i * 3) + 2] = vertex[i].z;
	}
	
	vertices = x;

	g1enVertexBuffer(&vertexBuffer, vertexBufferData, size);

	free(vertexBufferData);
}

int agl::GLPrimative::getMode()
{
	return mode;
}

unsigned int agl::GLPrimative::getVertexBuffer()
{
	return vertexBuffer;
}

int agl::GLPrimative::getVertices()
{
	return vertices;
}
