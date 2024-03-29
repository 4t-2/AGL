#include "../include/Cuboid.hpp"

#include "GL/gl.h"
#include <cstdio>
#include <cstdlib>

agl::Cuboid::Cuboid()
{
	GLfloat vertexBufferData[] = {
		0, 0, 0, // t1 v1
		0, 0, 1, // t1 v2
		0, 1, 1, // t1 v3
		1, 1, 0, // t2 v1
		0, 0, 0, // t2 v2
		0, 1, 0, // t2 v3
		1, 0, 1, // t3 v1
		0, 0, 0, // t3 v2
		1, 0, 0, // t3 v3
		1, 1, 0, // t4 v1
		1, 0, 0, // t4 v2
		0, 0, 0, // t4 v3
		0, 0, 0, // t5 v1
		0, 1, 1, // t5 v2
		0, 1, 0, // t5 v3
		1, 0, 1, // t6 v1
		0, 0, 1, // t6 v2
		0, 0, 0, // t6 v3
		0, 1, 1, // t7 v1
		0, 0, 1, // t7 v2
		1, 0, 1, // t7 v3
		1, 1, 1, // t8 v1
		1, 0, 0, // t8 v2
		1, 1, 0, // t8 v3
		1, 0, 0, // t9 v1
		1, 1, 1, // t9 v2
		1, 0, 1, // t9 v3
		1, 1, 1, // t10 v1
		1, 1, 0, // t10 v2
		0, 1, 0, // t10 v3
		1, 1, 1, // t11 v1
		0, 1, 0, // t11 v2
		0, 1, 1, // t11 v3
		1, 1, 1, // t12 v1
		0, 1, 1, // t12 v2
		1, 0, 1	 // t12 v3
	};

	float UVBufferData[] = {
		0.000059f, 1.0f - 0.000004f, // t1 v1
		0.000103f, 1.0f - 0.336048f, // t1 v2
		0.335973f, 1.0f - 0.335903f, // t1 v3
		1.000023f, 1.0f - 0.000013f, // t2 v1
		0.667979f, 1.0f - 0.335851f, // t2 v2
		0.999958f, 1.0f - 0.336064f, // t2 v3
		0.667979f, 1.0f - 0.335851f, // t3 v1
		0.336024f, 1.0f - 0.671877f, // t3 v2
		0.667969f, 1.0f - 0.671889f, // t3 v3
		1.000023f, 1.0f - 0.000013f, // t4 v1
		0.668104f, 1.0f - 0.000013f, // t4 v2
		0.667979f, 1.0f - 0.335851f, // t4 v3
		0.000059f, 1.0f - 0.000004f, // t5 v1
		0.335973f, 1.0f - 0.335903f, // t5 v2
		0.336098f, 1.0f - 0.000071f, // t5 v3
		0.667979f, 1.0f - 0.335851f, // t6 v1
		0.335973f, 1.0f - 0.335903f, // t6 v2
		0.336024f, 1.0f - 0.671877f, // t6 v3
		1.000004f, 1.0f - 0.671847f, // t7 v1
		0.999958f, 1.0f - 0.336064f, // t7 v2
		0.667979f, 1.0f - 0.335851f, // t7 v3
		0.668104f, 1.0f - 0.000013f, // t8 v1
		0.335973f, 1.0f - 0.335903f, // t8 v2
		0.667979f, 1.0f - 0.335851f, // t8 v3
		0.335973f, 1.0f - 0.335903f, // t9 v1
		0.668104f, 1.0f - 0.000013f, // t9 v2
		0.336098f, 1.0f - 0.000071f, // t9 v3
		0.000103f, 1.0f - 0.336048f, // t10 v1
		0.000004f, 1.0f - 0.671870f, // t10 v2
		0.336024f, 1.0f - 0.671877f, // t10 v3
		0.000103f, 1.0f - 0.336048f, // t11 v1
		0.336024f, 1.0f - 0.671877f, // t11 v2
		0.335973f, 1.0f - 0.335903f, // t11 v3
		0.667969f, 1.0f - 0.671889f, // t12 v1
		1.000004f, 1.0f - 0.671847f, // t12 v2
		0.667979f, 1.0f - 0.335851f	 // t12 v3
	};

	this->genBuffers();
	this->setMode(GL_TRIANGLES);
	this->setBufferData(vertexBufferData, UVBufferData, 36);

	offsetMatrix.translate(offset);
	translationMatrix.translate(position);
	scalingMatrix.scale(size);
	rotationMatrix.rotate(rotation);

	textureTranslation.translate({0, 0});
	textureScaling.scale({1, 1});
	
	return;
}
