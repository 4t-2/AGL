#include "../include/Shape.hpp"
#include <cstdio>
#include <cstdlib>
#include <glm/ext/matrix_float4x4.hpp>

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

void agl::Shape::setShapeData()
{
	int vertices = (shapeData.getVertexDataSize() / sizeof(float)) / 3;

	float *newVertexData = (float *)malloc(shapeData.getVertexDataSize());

	for (int i = 0; i < vertices; i++)
	{
		newVertexData[(i * 3) + 0] = (vertexData[(i * 3) + 0] * size.x) + position.x;
		newVertexData[(i * 3) + 1] = (vertexData[(i * 3) + 1] * size.y) + position.y;
		newVertexData[(i * 3) + 2] = (vertexData[(i * 3) + 2] * size.z) + position.z;
	}

	shapeData.setVertexData(newVertexData, shapeData.getVertexDataSize());

	free(newVertexData);

	return;
}

agl::GLPrimative agl::Shape::getShapeData()
{
	return shapeData;
}
