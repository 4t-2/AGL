#include "../include/Shape.hpp"
#include "../include/Mat4f.hpp"
#include <cstdio>
#include <cstdlib>

agl::Shape::~Shape()
{
	shapeData.deleteData();

	return;
}

void agl::Shape::setOffset(agl::Vec<float, 3> offset)
{
	this->offset = offset;

	offsetMatrix.translate(offset);

	return;
}

void agl::Shape::setPosition(agl::Vec<float, 3> position)
{
	this->position = position;

	translationMatrix.translate(position);

	return;
}

void agl::Shape::setPosition(agl::Vec<float, 2> position)
{
	this->position.x = position.x;
	this->position.y = position.y;

	translationMatrix.translate(this->position);

	return;
}

void agl::Shape::setSize(agl::Vec<float, 3> size)
{
	this->size = size;

	scalingMatrix.scale(size);

	return;
}

void agl::Shape::setSize(agl::Vec<float, 2> size)
{
	this->size.x = size.x;
	this->size.y = size.y;

	scalingMatrix.scale(this->size);

	return;
}

void agl::Shape::genBuffers()
{
	shapeData.genBuffers(2);

	return;
}

void agl::Shape::setMode(int mode)
{
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

void agl::Shape::setRotation(agl::Vec<float, 3> rotation)
{
	this->rotation = rotation;

	rotationMatrix.rotate(rotation);

	return;
}

void agl::Shape::setRotation(agl::Vec<float, 2> rotation)
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
	this->texture = texture;

	return;
}

void agl::Shape::setTextureTranslation(Vec<float, 2> translation)
{
	textureTranslation.translate(Vec<float, 3>{translation.x, translation.y, 0});
}

void agl::Shape::setTextureScaling(Vec<float, 2> scale)
{
	textureScaling.scale(Vec<float, 3>{scale.x, scale.y, 0});
}

agl::Vec<float, 3> agl::Shape::getOffset()
{
	return offset;
}

agl::Vec<float, 3> agl::Shape::getPosition()
{
	return position;
}

agl::Vec<float, 3> agl::Shape::getSize()
{
	return size;
}

agl::Vec<float, 3> agl::Shape::getRotation()
{
	return rotation;
}

agl::Color agl::Shape::getColor()
{
	return color;
}

agl::Texture *agl::Shape::getTexture()
{
	return texture;
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

agl::Mat4f agl::Shape::getTextureTranslation()
{
	return textureTranslation;
}

agl::Mat4f agl::Shape::getTextureScaling()
{
	return textureScaling;
}
