#include "../include/Rectangle.hpp"
#include <GL/gl.h>
#include <cstdlib>

agl::Rectangle::Rectangle()
{
	int dataSize = sizeof(float) * 12;

	float vertexBufferData[12];
	float colorBufferData[12];

	vertexBufferData[0]  = 0;
	vertexBufferData[1]  = 0;
	vertexBufferData[2]  = 0;
	vertexBufferData[3]  = 0 + 1;
	vertexBufferData[4]  = 0;
	vertexBufferData[5]  = 0;
	vertexBufferData[6]  = 0;
	vertexBufferData[7]  = 0 + 1;
	vertexBufferData[8]  = 0;
	vertexBufferData[9]  = 0 + 1;
	vertexBufferData[10] = 0 + 1;
	vertexBufferData[11] = 0;

	Vec3f colorNormalized = color.normalized();

	colorBufferData[0]  = colorNormalized.x;
	colorBufferData[1]  = colorNormalized.y;
	colorBufferData[2]  = colorNormalized.z;
	colorBufferData[3]  = colorNormalized.x;
	colorBufferData[4]  = colorNormalized.y;
	colorBufferData[5]  = colorNormalized.z;
	colorBufferData[6]  = colorNormalized.x;
	colorBufferData[7]  = colorNormalized.y;
	colorBufferData[8]  = colorNormalized.z;
	colorBufferData[9]  = colorNormalized.x;
	colorBufferData[10] = colorNormalized.y;
	colorBufferData[11] = colorNormalized.z;

	shapeData.setMode(GL_TRIANGLE_STRIP);
	shapeData.genBuffers(2);
	shapeData.setVertexAmount(4);
	shapeData.setBufferData(0, vertexBufferData, 3);
	shapeData.setBufferData(1, colorBufferData, 3);
}
