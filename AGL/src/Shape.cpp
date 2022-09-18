#include "../include/Shape.hpp"
#include "../include/Mat4f.hpp"
#include <cstdio>
#include <cstdlib>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <math.h>

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

void transform(glm::mat4 &mat, agl::Vec3f size, agl::Vec3f position)
{
	mat[3][3] = 1.0f;

	mat[0][0] = size.x;
	mat[1][1] = size.y;
	mat[2][2] = size.z;

	mat[3][0] = position.x;
	mat[3][1] = position.y;
	mat[3][2] = position.z;

	return;
}

void rotateX(glm::mat4 &mat, float x)
{
	mat[3][3] = 1.0f;
	mat[0][0] = 1.0f;

	float xSin = sin(x * 3.14 / 180);
	float xCos = cos(x * 3.14 / 180);

	mat[1][1] = xCos;
	mat[2][2] = xCos;
	mat[1][2] = xSin;
	mat[2][1] = -xSin;

	return;
}

void rotateY(glm::mat4 &mat, float y)
{
	mat[1][1] = 1.0f;
	mat[3][3] = 1.0f;

	float ySin = sin(y * 3.14 / 180);
	float yCos = cos(y * 3.14 / 180);

	mat[0][0] = yCos;
	mat[2][2] = yCos;
	mat[0][2] = ySin;
	mat[2][0] = -ySin;

	return;
}

void rotateZ(glm::mat4 &mat, float z)
{
	mat[2][2] = 1.0f;
	mat[3][3] = 1.0f;

	float zSin = sin(z * 3.14 / 180);
	float zCos = cos(z * 3.14 / 180);

	mat[0][0] = zCos;
	mat[1][1] = zCos;
	mat[1][0] = zSin;
	mat[0][1] = -zSin;

	return;
}

void agl::Shape::setShapeData()
{
	int vertices = (shapeData.getBufferSize() / sizeof(float)) / 3;

	glm::mat4 transformMatrix = glm::mat4();
	transform(transformMatrix, size, position);

	glm::mat4 xRotationMatrix = glm::mat4();
	rotateX(xRotationMatrix, rotation.x);
	glm::mat4 yRotationMatrix = glm::mat4();
	rotateY(yRotationMatrix, rotation.y);
	glm::mat4 zRotationMatrix = glm::mat4();
	rotateZ(zRotationMatrix, rotation.z);

	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	// glm::mat4 rotationMatrix = xRotationMatrix * yRotationMatrix * zRotationMatrix;

	agl::Mat4f translate;
	translate.translate(position);

	float *newVertexData = (float *)malloc(shapeData.getBufferSize());

	for (int i = 0; i < vertices; i++)
	{
		agl::Vec4f oldPos;
		oldPos.x = vertexData[(i * 3) + 0];
		oldPos.y = vertexData[(i * 3) + 1];
		oldPos.z = vertexData[(i * 3) + 2];
		oldPos.w = 1.0f;

		// glm::vec4 newPos = rotationMatrix * transformMatrix * oldPos;
		Vec4f newPos = translate.multiply(oldPos);
	
		newVertexData[(i * 3) + 0] = newPos.x;
		newVertexData[(i * 3) + 1] = newPos.y;
		newVertexData[(i * 3) + 2] = newPos.z;
	}

	shapeData.setVertexData(newVertexData);

	free(newVertexData);

	return;
}

agl::GLPrimative agl::Shape::getShapeData()
{
	return shapeData;
}
