#include "../include/Shape.hpp"
#include <cstdlib>
#include <glm/ext/matrix_float4x4.hpp>

agl::Shape::~Shape()
{
	free(vertexData);
	free(colorData);

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

agl::GLPrimative agl::Shape::getShapeData()
{
	return shapeData;
}
