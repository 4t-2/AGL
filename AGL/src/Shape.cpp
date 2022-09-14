#include "../include/Shape.hpp"
#include <cstdio>
#include <cstdlib>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

agl::Shape::~Shape()
{
	free(vertexData);
	free(colorData);
	shapeData.deleteData();

	return;
}

void agl::Shape::setPosition(agl::Vec3f position)
{
	this->position = position;

	return;
}

void agl::Shape::setPosition(agl::Vec2f position)
{
	this->position.x = position.x;
	this->position.y = position.y;

	return;
}

void agl::Shape::setSize(agl::Vec3f size)
{
	this->size = size;

	return;
}

void agl::Shape::setSize(agl::Vec2f size)
{
	this->size.x = size.x;
	this->size.y = size.y;

	return;
}

void agl::Shape::setColor(agl::Color color)
{
	this->color = color;

	return;
}

void transform(glm::mat4 &mat, agl::Vec3f size, agl::Vec3f position)
{
	mat[3][3] = 1.0f;

	mat[0][0] = size.x;
	mat[1][1] = size.y;
	mat[2][2] = size.z;

	mat[3][0] = position.x;
	mat[3][1] = position.y;
	mat[3][2] = position.z;

	return;
}

void agl::Shape::setShapeData()
{
	int vertices = (shapeData.getVertexDataSize() / sizeof(float)) / 3;

	glm::mat4 transformMatrix = glm::mat4();
	transform(transformMatrix, size, position);

	float *newVertexData = (float *)malloc(shapeData.getVertexDataSize());

	for (int i = 0; i < vertices; i++)
	{
		glm::vec4 oldPos;
		oldPos.x = vertexData[(i * 3) + 0];
		oldPos.y = vertexData[(i * 3) + 1];
		oldPos.z = vertexData[(i * 3) + 2];
		oldPos.w = 1.0f;

		glm::vec4 newPos = transformMatrix * oldPos;

		newVertexData[(i * 3) + 0] = newPos.x;
		newVertexData[(i * 3) + 1] = newPos.y;
		newVertexData[(i * 3) + 2] = newPos.z;
	}

	shapeData.setVertexData(newVertexData, shapeData.getVertexDataSize());

	free(newVertexData);

	return;
}

agl::GLPrimative agl::Shape::getShapeData()
{
	return shapeData;
}
