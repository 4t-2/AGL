#include "../include/Rectangle.hpp"

void agl::Rectangle::setSize(agl::Vec2f size)
{
	this->size = size;

	return;
}

void agl::Rectangle::setPosition(agl::Vec2f position)
{
	this->position = position;

	return;
}

void agl::Rectangle::setColor(agl::Color color)
{
	this->color = color;

	return;
}

agl::Vec2f agl::Rectangle::getSize()
{
	return size;
}

agl::Vec2f agl::Rectangle::getPosition()
{
	return position;
}

agl::Color agl::Rectangle::getColor()
{
	return color;
}
