#include "../include/Circle.hpp"
#include <cstdio>
#include <cstdlib>
#include <math.h>

agl::Circle::Circle(unsigned int faces)
{
	int size = sizeof(float) * 3 * (faces + 2);

	float *vertexBufferData = (float *)malloc(size);
	float *colorBufferData  = (float *)malloc(size);

	vertexBufferData[0] = 0;
	vertexBufferData[1] = 0;
	vertexBufferData[2] = 0;

	for (int i = 1; i < (faces + 1); i++)
	{
		float angle = (360. / faces) * i;

		float x = cos(angle * (3.14159 / 180));
		float y = sin(angle * (3.14159 / 180));

		vertexBufferData[(i * 3) + 0] = x;
		vertexBufferData[(i * 3) + 1] = y;
		vertexBufferData[(i * 3) + 2] = 0;
	}

	vertexBufferData[((faces + 1) * 3) + 0] = vertexBufferData[((1) * 3) + 0];
	vertexBufferData[((faces + 1) * 3) + 1] = vertexBufferData[((1) * 3) + 1];
	vertexBufferData[((faces + 1) * 3) + 2] = vertexBufferData[((1) * 3) + 2];

	colorBufferData[0]  = 1;
	colorBufferData[1]  = 0;
	colorBufferData[2]  = 0;
	colorBufferData[3]  = 0;
	colorBufferData[4]  = 1;
	colorBufferData[5]  = 0;
	colorBufferData[6]  = 0;
	colorBufferData[7]  = 0;
	colorBufferData[8]  = 1;
	colorBufferData[9]  = 1;
	colorBufferData[10] = 0;
	colorBufferData[11] = 0;
	colorBufferData[12] = 0;
	colorBufferData[13] = 1;
	colorBufferData[14] = 0;

	shapeData.setMode(GL_TRIANGLE_FAN);

	shapeData.genBuffers(2);
	shapeData.setVertexAmount(faces + 2);
	shapeData.setBufferData(0, vertexBufferData, 3);
	shapeData.setBufferData(1, colorBufferData, 3);

	free(vertexBufferData);
	free(colorBufferData);

	return;
}
