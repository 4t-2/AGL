#include "../include/Rectangle.hpp"
#include <GL/gl.h>
#include <cstdlib>

agl::Rectangle::Rectangle()
{
	float vertexBufferData[12];
	float UVBufferData[8];

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

	UVBufferData[0] = vertexBufferData[0];
	UVBufferData[1] = vertexBufferData[1];
	UVBufferData[2] = vertexBufferData[3];
	UVBufferData[3] = vertexBufferData[4];
	UVBufferData[4] = vertexBufferData[6];
	UVBufferData[5] = vertexBufferData[7];
	UVBufferData[6] = vertexBufferData[9];
	UVBufferData[7] = vertexBufferData[10];

	this->genBuffers(GL_TRIANGLE_STRIP);
	this->setBufferData(vertexBufferData, UVBufferData, 4);

	return;
}
