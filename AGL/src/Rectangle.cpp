#include "../include/Rectangle.hpp"
#include <GL/gl.h>

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

void agl::Rectangle::setData()
{
	float vertexData[12] = {
		position.x,			 position.y,		  0, // 1
		position.x + size.x, position.y,		  0, // 2
		position.x,			 position.y + size.y, 0, // 3
		position.x + size.x, position.y + size.y, 0, // 4
	};
	
	Vec3f colorNormalized = color.normalized();

	float colorData[12] = {
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // 1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // 2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // 3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // 4
	};

	shape.setMode(GL_TRIANGLE_STRIP);
	shape.setVertexData(vertexData, sizeof(vertexData));
	shape.setColorData(colorData, sizeof(colorData));

	return;
}

void agl::Rectangle::deleteData()
{
	shape.deleteData();
}

agl::GLPrimative agl::Rectangle::getShape()
{
	return shape;
}
