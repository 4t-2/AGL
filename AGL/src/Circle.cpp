#include "../include/Circle.hpp"
#include <cstdio>
#include <cstdlib>
#include "../include/math.hpp"

agl::Circle::Circle(unsigned int faces)
{
	int vertices = (faces + 2);

	float *vertexBufferData = (float *)malloc(vertices * 3 * sizeof(float));
	float *UVBufferData		= (float *)malloc(vertices * 2 * sizeof(float));

	vertexBufferData[0] = 0;
	vertexBufferData[1] = 0;
	vertexBufferData[2] = 0;

	for (int i = 1; i < (vertices - 1); i++)
	{
		float angle = (PI * 2 / faces) * i;

		Vec<float, 2> position = pointOnCircle(angle);

		vertexBufferData[(i * 3) + 0] = position.x;
		vertexBufferData[(i * 3) + 1] = position.y;
		vertexBufferData[(i * 3) + 2] = 0;
	}

	vertexBufferData[((vertices - 1) * 3) + 0] = vertexBufferData[((1) * 3) + 0];
	vertexBufferData[((vertices - 1) * 3) + 1] = vertexBufferData[((1) * 3) + 1];
	vertexBufferData[((vertices - 1) * 3) + 2] = vertexBufferData[((1) * 3) + 2];

	for (int i = 0; i < vertices; i++)
	{
		UVBufferData[(i * 2) + 0] = (vertexBufferData[(i * 3) + 0] / 2) + 0.5;
		UVBufferData[(i * 2) + 1] = (vertexBufferData[(i * 3) + 1] / 2) + 0.5;
	}

	this->genBuffers();
	this->setMode(GL_TRIANGLE_FAN);
	this->setBufferData(vertexBufferData, UVBufferData, vertices);

	free(vertexBufferData);
	free(UVBufferData);

	offsetMatrix.translate(offset);
	translationMatrix.translate(position);
	scalingMatrix.scale(size);
	rotationMatrix.rotate(rotation);

	textureTranslation.translate({0, 0});
	textureScaling.scale({1, 1});

	return;
}
