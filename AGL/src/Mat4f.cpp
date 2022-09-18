#include "../include/Mat4f.hpp"
#include <cstdio>

void agl::Mat4f::identity()
{
	data[0][0] = 1;
	data[1][1] = 1;
	data[2][2] = 1;
	data[3][3] = 1;

	return;
}

void agl::Mat4f::translate(agl::Vec3f vector)
{
	data[0][0] = 1;
	data[1][1] = 1;
	data[2][2] = 1;
	data[3][3] = 1;

	data[3][0] = vector.x;
	data[3][1] = vector.y;
	data[3][2] = vector.z;

	return;
}

void agl::Mat4f::scale(agl::Vec3f vector)
{
	data[0][0] = vector.x;
	data[1][1] = vector.y;
	data[2][2] = vector.z;
	data[3][3] = 1;

	return;
}

agl::Mat4f agl::Mat4f::multiply(agl::Mat4f matrix)
{
	Mat4f newMatrix;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			newMatrix.data[x][y] = data[x][y] * matrix.data[y][x];
		}
	}

	return newMatrix;
}

agl::Vec4f agl::Mat4f::multiply(agl::Vec4f vector)
{
	Vec4f newVector;

	newVector.x = (data[0][0] * vector.x) + (data[1][0] * vector.y) + (data[2][0] * vector.z) + (data[3][0] * vector.w);
	newVector.y = (data[0][1] * vector.x) + (data[1][1] * vector.y) + (data[2][1] * vector.z) + (data[3][1] * vector.w);
	newVector.z = (data[0][2] * vector.x) + (data[1][2] * vector.y) + (data[2][2] * vector.z) + (data[3][2] * vector.w);
	newVector.w = (data[0][3] * vector.x) + (data[1][3] * vector.y) + (data[2][3] * vector.z) + (data[3][3] * vector.w);

	return newVector;
}
