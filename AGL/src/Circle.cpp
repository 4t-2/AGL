#include "../include/Circle.hpp"
#include <cstdio>
#include <cstdlib>
#include <math.h>

agl::Circle::Circle(unsigned int faces)
{

	vertexData = (float *)malloc(sizeof(float*) * 15);

	vertexData[0] = 0;
	vertexData[1] = 0;
	vertexData[2] = 0;

	vertexData[3] = 1;
	vertexData[4] = 1;
	vertexData[5] = 0;

	vertexData[6] = -1;
	vertexData[7] = 1;
	vertexData[8] = 0;

	vertexData[9]  = -1;
	vertexData[10] = -1;
	vertexData[11] = 0;

	vertexData[12] = 1;
	vertexData[13] = -1;
	vertexData[14] = 0;

	float colorData[] = {
		1, 0, 0, // 1
		0, 1, 0, // 1
		0, 0, 1, // 1
		1, 0, 0, // 1
		0, 1, 0, // 1
	};

	shape.setMode(GL_LINE_STRIP);
	shape.setVertexData(vertexData, sizeof(vertexData));
	shape.setColorData(colorData, sizeof(colorData));

	return;
}

agl::GLPrimative agl::Circle::getShape()
{
	return shape;
}
