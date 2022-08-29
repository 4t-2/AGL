#include "../include/Rectangle.hpp"

void agl::Rectangle::setSize(agl::Float2 size)
{
	this->size = size;

	return;
}

void agl::Rectangle::setPosition(agl::Float2 position)
{
	this->position = position;

	return;
}

void agl::Rectangle::setColor(agl::Color color)
{
	this->color = color;

	return;
}

agl::Float2 agl::Rectangle::getSize()
{
	return size;
}

agl::Float2 agl::Rectangle::getPosition()
{
	return position;
}

agl::Color agl::Rectangle::getColor()
{
	return color;
}
