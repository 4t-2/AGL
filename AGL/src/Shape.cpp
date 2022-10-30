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

void agl::Shape::setOffset(agl::Vec3f offset)
{
	this->offset = offset;

	offsetMatrix.translate(offset);

	return;
}

void agl::Shape::setPosition(agl::Vec3f position)
{
	this->position = position;

	translationMatrix.translate(position);

	return;
}

void agl::Shape::setPosition(agl::Vec2f position)
{
	this->position.x = position.x;
	this->position.y = position.y;

	translationMatrix.translate(this->position);

	return;
}

void agl::Shape::setSize(agl::Vec3f size)
{
	this->size = size;

	scalingMatrix.scale(size);

	return;
}

void agl::Shape::setSize(agl::Vec2f size)
{
	this->size.x = size.x;
	this->size.y = size.y;

	scalingMatrix.scale(this->size);

	return;
}

void agl::Shape::genBuffers(int mode)
{
	shapeData.genBuffers(2);
	shapeData.setMode(mode);

	return;
}

void agl::Shape::setBufferData(float vertexBufferData[], float UVBufferData[], int vertices)
{
	shapeData.setVertexAmount(vertices);
	shapeData.setBufferData(0, vertexBufferData, 3);
	shapeData.setBufferData(1, UVBufferData, 2);

	return;
}

void agl::Shape::setRotation(agl::Vec3f rotation)
{
	this->rotation = rotation;

	rotationMatrix.rotate(rotation);

	return;
}

void agl::Shape::setRotation(agl::Vec2f rotation)
{
	this->rotation.x = rotation.x;
	this->rotation.y = rotation.y;

	rotationMatrix.rotate(this->rotation);

	return;
}

void agl::Shape::setColor(agl::Color color)
{
	this->color = color;

	return;
}

void agl::Shape::setTexture(Texture *texture)
{
	textureID = texture->getTextureID();

	return;
}

agl::Vec3f agl::Shape::getOffset()
{
	return offset;
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

int agl::Shape::getTextureID()
{
	return textureID;
}

agl::Mat4f agl::Shape::getOffsetMatrix()
{
	return offsetMatrix;
}

agl::Mat4f agl::Shape::getTranslationMatrix()
{
	return translationMatrix;
}

agl::Mat4f agl::Shape::getScalingMatrix()
{
	return scalingMatrix;
}

agl::Mat4f agl::Shape::getRotationMatrix()
{
	return rotationMatrix;
}

agl::GLPrimative agl::Shape::getShapeData()
{
	return shapeData;
}
