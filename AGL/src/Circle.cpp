#include "../include/Circle.hpp"
#include <cstdio>
#include <cstdlib>
#include <math.h>

agl::Circle::Circle(unsigned int faces)
{
	int size = sizeof(float) * 3 * (faces + 2);

	vertexData = (float *)malloc(size);

	vertexData[0] = 0;
	vertexData[1] = 0;
	vertexData[2] = 0;

	for (int i = 1; i < (faces + 1); i++)
	{
		float angle = (360. / faces) * i;

		float x = cos(angle * (3.14159 / 180));
		float y = sin(angle * (3.14159 / 180));

		vertexData[(i * 3) + 0] = x;
		vertexData[(i * 3) + 1] = y;
		vertexData[(i * 3) + 2] = 0;
	}

	vertexData[((faces+1) * 3) + 0] = vertexData[((1) * 3) + 0];
	vertexData[((faces+1) * 3) + 1] = vertexData[((1) * 3) + 1];
	vertexData[((faces+1) * 3) + 2] = vertexData[((1) * 3) + 2];

	for (int i = 0; i < (faces + 2); i++)
	{
		printf("%d\n", i);
		printf("%f\n", vertexData[i * 3 + 0]);
		printf("%f\n", vertexData[i * 3 + 1]);
		printf("%f\n", vertexData[i * 3 + 2]);
		printf("\n");
	}

	float colorData[] = {
		1, 0, 0, // 1
		0, 1, 0, // 1
		0, 0, 1, // 1
		1, 0, 0, // 1
		0, 1, 0, // 1
	};

	shape.setMode(GL_TRIANGLE_FAN);
	shape.setVertexData(vertexData, size);
	shape.setColorData(colorData, sizeof(colorData));

	return;
}

agl::GLPrimative agl::Circle::getShape()
{
	return shape;
}
