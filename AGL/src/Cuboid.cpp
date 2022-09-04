#include "../include/Cuboid.hpp"

#include "GL/gl.h"

void agl::Cuboid::setSizePosition(agl::Vec3f size, agl::Vec3f position)
{
	GLfloat vertexBufferData[] = {
		position.x,			 position.y,		  position.z,		   // t1 v1
		position.x,			 position.y,		  position.z + size.z, // t1 v2
		position.x,			 position.y + size.y, position.z + size.z, // t1 v3
		position.x + size.x, position.y + size.y, position.z,		   // t2 v1
		position.x,			 position.y,		  position.z,		   // t2 v2
		position.x,			 position.y + size.y, position.z,		   // t2 v3
		position.x + size.x, position.y,		  position.z + size.z, // t3 v1
		position.x,			 position.y,		  position.z,		   // t3 v2
		position.x + size.x, position.y,		  position.z,		   // t3 v3
		position.x + size.x, position.y + size.y, position.z,		   // t4 v1
		position.x + size.x, position.y,		  position.z,		   // t4 v2
		position.x,			 position.y,		  position.z,		   // t4 v3
		position.x,			 position.y,		  position.z,		   // t5 v1
		position.x,			 position.y + size.y, position.z + size.z, // t5 v2
		position.x,			 position.y + size.y, position.z,		   // t5 v3
		position.x + size.x, position.y,		  position.z + size.z, // t6 v1
		position.x,			 position.y,		  position.z + size.z, // t6 v2
		position.x,			 position.y,		  position.z,		   // t6 v3
		position.x,			 position.y + size.y, position.z + size.z, // t7 v1
		position.x,			 position.y,		  position.z + size.z, // t7 v2
		position.x + size.x, position.y,		  position.z + size.z, // t7 v3
		position.x + size.x, position.y + size.y, position.z + size.z, // t8 v1
		position.x + size.x, position.y,		  position.z,		   // t8 v2
		position.x + size.x, position.y + size.y, position.z,		   // t8 v3
		position.x + size.x, position.y,		  position.z,		   // t9 v1
		position.x + size.x, position.y + size.y, position.z + size.z, // t9 v2
		position.x + size.x, position.y,		  position.z + size.z, // t9 v3
		position.x + size.x, position.y + size.y, position.z + size.z, // t10 v1
		position.x + size.x, position.y + size.y, position.z,		   // t10 v2
		position.x,			 position.y + size.y, position.z,		   // t10 v3
		position.x + size.x, position.y + size.y, position.z + size.z, // t11 v1
		position.x,			 position.y + size.y, position.z,		   // t11 v2
		position.x,			 position.y + size.y, position.z + size.z, // t11 v3
		position.x + size.x, position.y + size.y, position.z + size.z, // t12 v1
		position.x,			 position.y + size.y, position.z + size.z, // t12 v2
		position.x + size.x, position.y,		  position.z + size.z  // t12 v3
	};

	// GLfloat vertexBufferData[] = {
	// 	-1.0f, -1.0f, -1.0f, // t1 v1
	// 	-1.0f, -1.0f, 1.0f,	 // t1 v2
	// 	-1.0f, 1.0f,  1.0f,	 // t1 v3
	// 	1.0f,  1.0f,  -1.0f, // t2 v1
	// 	-1.0f, -1.0f, -1.0f, // t2 v2
	// 	-1.0f, 1.0f,  -1.0f, // t2 v3
	// 	1.0f,  -1.0f, 1.0f,	 // t3 v1
	// 	-1.0f, -1.0f, -1.0f, // t3 v2
	// 	1.0f,  -1.0f, -1.0f, // t3 v3
	// 	1.0f,  1.0f,  -1.0f, // t4 v1
	// 	1.0f,  -1.0f, -1.0f, // t4 v2
	// 	-1.0f, -1.0f, -1.0f, // t4 v3
	// 	-1.0f, -1.0f, -1.0f, // t5 v1
	// 	-1.0f, 1.0f,  1.0f,	 // t5 v2
	// 	-1.0f, 1.0f,  -1.0f, // t5 v3
	// 	1.0f,  -1.0f, 1.0f,	 // t6 v1
	// 	-1.0f, -1.0f, 1.0f,	 // t6 v2
	// 	-1.0f, -1.0f, -1.0f, // t6 v3
	// 	-1.0f, 1.0f,  1.0f,	 // t7 v1
	// 	-1.0f, -1.0f, 1.0f,	 // t7 v2
	// 	1.0f,  -1.0f, 1.0f,	 // t7 v3
	// 	1.0f,  1.0f,  1.0f,	 // t8 v1
	// 	1.0f,  -1.0f, -1.0f, // t8 v2
	// 	1.0f,  1.0f,  -1.0f, // t8 v3
	// 	1.0f,  -1.0f, -1.0f, // t9 v1
	// 	1.0f,  1.0f,  1.0f,	 // t9 v2
	// 	1.0f,  -1.0f, 1.0f,	 // t9 v3
	// 	1.0f,  1.0f,  1.0f,	 // t10 v1
	// 	1.0f,  1.0f,  -1.0f, // t10 v2
	// 	-1.0f, 1.0f,  -1.0f, // t10 v3
	// 	1.0f,  1.0f,  1.0f,	 // t11 v1
	// 	-1.0f, 1.0f,  -1.0f, // t11 v2
	// 	-1.0f, 1.0f,  1.0f,	 // t11 v3
	// 	1.0f,  1.0f,  1.0f,	 // t12 v1
	// 	-1.0f, 1.0f,  1.0f,	 // t12 v2
	// 	1.0f,  -1.0f, 1.0f	 // t12 v3
	// };

	shape.setMode(GL_TRIANGLES);
	shape.setVertexData(vertexBufferData, sizeof(vertexBufferData));

	return;
}

void agl::Cuboid::setColor(agl::Color color)
{
	Vec3f colorNormalized = color.normalized();

	float colorBufferData[] = {
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t1 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t1 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t1 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t2 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t2 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t2 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t3 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t3 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t3 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t4 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t4 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t4 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t5 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t5 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t5 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t6 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t6 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t6 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t7 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t7 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t7 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t8 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t8 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t8 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t9 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t9 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t9 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t10 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t10 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t10 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t11 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t11 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t11 v3
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t12 v1
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t12 v2
		colorNormalized.x, colorNormalized.y, colorNormalized.z, // t12 v3
	};

	shape.setColorData(colorBufferData, sizeof(colorBufferData));

	return;
}

void agl::Cuboid::deleteData()
{
	shape.deleteData();

	return;
}

agl::GLPrimative agl::Cuboid::getShape()
{
	return shape;
}
