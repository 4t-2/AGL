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

void agl::Shape::genBuffers(int vertices)
{
	shapeData.genBuffers(2);
	shapeData.setVertexAmount(vertices);
	shapeData.setMode(GL_TRIANGLES);

	return;
}

void agl::Shape::setBufferData(Vec3f vertexBufferData[], Vec2f UVBufferData[])
{
	int vertexVertices = shapeData.getVertexAmount() * 3;
	int UVvertices = shapeData.getVertexAmount() * 2;

	float *vertexBufferDataFloat = (float*)malloc(vertexVertices * sizeof(float));
	float *UVBufferDataFloat = (float*)malloc(UVvertices * sizeof(float));

	for(int i = 0; i < vertexVertices / 3; i++)
	{
		vertexBufferDataFloat[i*3+0] = vertexBufferData[i].x;
		vertexBufferDataFloat[i*3+1] = vertexBufferData[i].y;
		vertexBufferDataFloat[i*3+2] = vertexBufferData[i].z;
	}

	free(vertexBufferDataFloat);
	free(UVBufferDataFloat);

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

void agl::Shape::setTexture(Texture *texture)
{
	textureID = texture->getTextureID();

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

int agl::Shape::getTextureID()
{
	return textureID;
}

agl::GLPrimative agl::Shape::getShapeData()
{
	return shapeData;
}
