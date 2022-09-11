#include "../include/Rectangle.hpp"
#include <GL/gl.h>
#include <cstdlib>

agl::Rectangle::Rectangle()
{
	int dataSize = sizeof(float) * 12;

	vertexData = (float *)malloc(dataSize);
	colorData  = (float *)malloc(dataSize);

	vertexData[0]  = 0;
	vertexData[1]  = 0;
	vertexData[2]  = 0;
	vertexData[3]  = 0 + 1;
	vertexData[4]  = 0;
	vertexData[5]  = 0;
	vertexData[6]  = 0;
	vertexData[7]  = 0 + 1;
	vertexData[8]  = 0;
	vertexData[9]  = 0 + 1;
	vertexData[10] = 0 + 1;
	vertexData[11] = 0;

	Vec3f colorNormalized = color.normalized();

	colorData[0]  = colorNormalized.x;
	colorData[1]  = colorNormalized.y;
	colorData[2]  = colorNormalized.z;
	colorData[3]  = colorNormalized.x;
	colorData[4]  = colorNormalized.y;
	colorData[5]  = colorNormalized.z;
	colorData[6]  = colorNormalized.x;
	colorData[7]  = colorNormalized.y;
	colorData[8]  = colorNormalized.z;
	colorData[9]  = colorNormalized.x;
	colorData[10] = colorNormalized.y;
	colorData[11] = colorNormalized.z;

	shapeData.setMode(GL_TRIANGLE_STRIP);
	shapeData.setVertexData(vertexData, dataSize);
	shapeData.setColorData(colorData, dataSize);
}
