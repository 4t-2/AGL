#include "../include/Circle.hpp"
#include <cstdio>
#include <cstdlib>
#include <math.h>

agl::Circle::Circle(unsigned int faces)
{
	int size = sizeof(float) * 3 * (faces + 2);

	vertexData = (float *)malloc(size);
	colorData  = (float *)malloc(size);

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

	vertexData[((faces + 1) * 3) + 0] = vertexData[((1) * 3) + 0];
	vertexData[((faces + 1) * 3) + 1] = vertexData[((1) * 3) + 1];
	vertexData[((faces + 1) * 3) + 2] = vertexData[((1) * 3) + 2];

	colorData[0]  = 1;
	colorData[1]  = 0;
	colorData[2]  = 0;
	colorData[3]  = 0;
	colorData[4]  = 1;
	colorData[5]  = 0;
	colorData[6]  = 0;
	colorData[7]  = 0;
	colorData[8]  = 1;
	colorData[9]  = 1;
	colorData[10] = 0;
	colorData[11] = 0;
	colorData[12] = 0;
	colorData[13] = 1;
	colorData[14] = 0;

	shapeData.setMode(GL_TRIANGLE_FAN);

	shapeData.genBuffers(2);
	shapeData.setVertexAmount(faces + 2);
	shapeData.setBufferData(0, vertexData, 3);
	shapeData.setBufferData(1, colorData, 3);

	// shapeData.setBufferSize(size);
	// shapeData.genVertexBuffer();
	// shapeData.setVertexData(vertexData);
	// shapeData.genColorBuffer();
	// shapeData.setColorData(colorData);

	return;
}
