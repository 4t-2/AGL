#include "../include/Shape.hpp"
#include "../include/Mat4f.hpp"
#include <cstdio>
#include <cstdlib>
#include <math.h>

agl::Shape::~Shape()
{
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

void agl::Shape::setRotation(agl::Vec3f rotation)
{
	this->rotation = rotation;

	return;
}

void agl::Shape::setRotation(agl::Vec2f rotation)
{
	this->rotation.x = rotation.x;
	this->rotation.y = rotation.y;

	return;
}

void agl::Shape::setColor(agl::Color color)
{
	this->color = color;

	return;
}

agl::Vec3f agl::Shape::getPosition()
{
	return position;
}

agl::Vec3f agl::Shape::getSize()
{
	return size;
}

agl::Vec3f agl::Shape::getRotation()
{
	return rotation;
}

agl::Color agl::Shape::getColor()
{
	return color;
}

agl::GLPrimative agl::Shape::getShapeData()
{
	return shapeData;
}
