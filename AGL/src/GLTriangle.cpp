#include <GL/glew.h>

#include <stdio.h>

#include "../include/GLTriangle.hpp"

void genVertexBuffer(GLuint *vertexBuffer, GLfloat *vertexBufferData)
{
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, vertexBuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertexBufferData)+1)*4, vertexBufferData, GL_STATIC_DRAW);
	return;
}

void agl::GLTriangle::setVertices(agl::Vector3f vertex[3])
{
	vertexBufferData[0] = vertex[0].x;
	vertexBufferData[1] = vertex[0].y;
	vertexBufferData[2] = vertex[0].z;

	vertexBufferData[3] = vertex[1].x;
	vertexBufferData[4] = vertex[1].y;
	vertexBufferData[5] = vertex[1].z;

	vertexBufferData[6] = vertex[2].x;
	vertexBufferData[7] = vertex[2].y;
	vertexBufferData[8] = vertex[2].z;

	genVertexBuffer(&vertexBuffer, vertexBufferData);

	return;
}

void agl::GLTriangle::setVertices(agl::Vector3f vertex1, agl::Vector3f vertex2, agl::Vector3f vertex3)
{
	vertexBufferData[0] = vertex1.x;
	vertexBufferData[1] = vertex1.y;
	vertexBufferData[2] = vertex1.z;

	vertexBufferData[3] = vertex2.x;
	vertexBufferData[4] = vertex2.y;
	vertexBufferData[5] = vertex2.z;

	vertexBufferData[6] = vertex3.x;
	vertexBufferData[7] = vertex3.y;
	vertexBufferData[8] = vertex3.z;

	genVertexBuffer(&vertexBuffer, vertexBufferData);

	return;
}
