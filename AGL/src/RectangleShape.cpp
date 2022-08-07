#include "../include/RectangleShape.hpp"

void agl::RectangleShape::setSize(agl::Vector2f size)
{
	this->size = size;

	return;
}

void agl::RectangleShape::setPosition(agl::Vector2f position)
{
	this->position = position;

	return;
}

void agl::RectangleShape::setColor(agl::Vector4f color)
{
	this->color = color;

	return;
}

agl::Vector2f agl::RectangleShape::getSize()
{
	return size;
}

agl::Vector2f agl::RectangleShape::getPosition()
{
	return position;
}
