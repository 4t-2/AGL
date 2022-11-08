#include "../include/Mat4f.hpp"
#include <math.h>

agl::Mat4f agl::Mat4f::operator*(agl::Mat4f matrix)
{
	agl::Mat4f newMatrix;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				newMatrix.data[i][j] += matrix.data[i][k] * data[k][j];
			}
		}
	}

	return newMatrix;
}

agl::Vec<float, 4> agl::Mat4f::operator*(agl::Vec<float, 4> vector)
{
	Vec<float, 4> newVector;

	newVector.x = (data[0][0] * vector.x) + (data[1][0] * vector.y) + (data[2][0] * vector.z) + (data[3][0] * vector.w);
	newVector.y = (data[0][1] * vector.x) + (data[1][1] * vector.y) + (data[2][1] * vector.z) + (data[3][1] * vector.w);
	newVector.z = (data[0][2] * vector.x) + (data[1][2] * vector.y) + (data[2][2] * vector.z) + (data[3][2] * vector.w);
	newVector.w = (data[0][3] * vector.x) + (data[1][3] * vector.y) + (data[2][3] * vector.z) + (data[3][3] * vector.w);

	return newVector;
}
void agl::Mat4f::identity()
{
	data[0][0] = 1;
	data[1][1] = 1;
	data[2][2] = 1;
	data[3][3] = 1;

	return;
}

void agl::Mat4f::translate(agl::Vec<float, 3> translation)
{
	data[0][0] = 1;
	data[1][1] = 1;
	data[2][2] = 1;
	data[3][3] = 1;

	data[3][0] = translation.x;
	data[3][1] = translation.y;
	data[3][2] = translation.z;

	return;
}

void agl::Mat4f::scale(agl::Vec<float, 3> scale)
{
	data[0][0] = scale.x;
	data[1][1] = scale.y;
	data[2][2] = scale.z;
	data[3][3] = 1;

	return;
}

void agl::Mat4f::rotateX(float x)
{
	data[3][3] = 1.0f;
	data[0][0] = 1.0f;

	float xSin = sin(x * 3.14 / 180);
	float xCos = cos(x * 3.14 / 180);

	data[1][1] = xCos;
	data[2][2] = xCos;
	data[1][2] = xSin;
	data[2][1] = -xSin;

	return;
}

void agl::Mat4f::rotateY(float y)
{
	data[1][1] = 1.0f;
	data[3][3] = 1.0f;

	float ySin = sin(y * 3.14 / 180);
	float yCos = cos(y * 3.14 / 180);

	data[0][0] = yCos;
	data[2][2] = yCos;
	data[0][2] = ySin;
	data[2][0] = -ySin;

	return;
}

void agl::Mat4f::rotateZ(float z)
{
	data[2][2] = 1.0f;
	data[3][3] = 1.0f;

	float zSin = sin(z * 3.14 / 180);
	float zCos = cos(z * 3.14 / 180);

	data[0][0] = zCos;
	data[1][1] = zCos;
	data[1][0] = zSin;
	data[0][1] = -zSin;

	return;
}

void agl::Mat4f::rotate(agl::Vec<float, 3> rotation) // HACK lazy and can definately be optimized
{
	Mat4f rotationX;
	Mat4f rotationY;
	Mat4f rotationZ;
	Mat4f rotationTotal;

	rotationX.rotateX(rotation.x);
	rotationY.rotateY(rotation.y);
	rotationZ.rotateZ(rotation.z);

	rotationTotal = rotationX * rotationY * rotationZ;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			data[x][y] = rotationTotal.data[x][y];
		}
	}

	return;
}

agl::Vec<float, 3> normalize(agl::Vec<float, 3> v)
{
	float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return {v.x /= len, v.y /= len, v.z /= len};
}

agl::Vec<float, 3> cross(const agl::Vec<float, 3> a, const agl::Vec<float, 3> b)
{
	return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

float dot(agl::Vec<float, 3> a, agl::Vec<float, 3> b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

void agl::Mat4f::lookAt(Vec<float, 3> pos, Vec<float, 3> target, Vec<float, 3> head)
{
	agl::Vec<float, 3> f = (normalize(target - pos));
	agl::Vec<float, 3> s = (normalize(cross(f, head)));
	agl::Vec<float, 3> u = (cross(s, f));

	data[0][0] = s.x;
	data[1][0] = s.y;
	data[2][0] = s.z;
	data[0][1] = u.x;
	data[1][1] = u.y;
	data[2][1] = u.z;
	data[0][2] = -f.x;
	data[1][2] = -f.y;
	data[2][2] = -f.z;
	data[3][0] = -dot(s, pos);
	data[3][1] = -dot(u, pos);
	data[3][2] = dot(f, pos);

	data[3][3] = 1.0f;

	return;
}

void agl::Mat4f::perspective(float fov, float aspectRatio, float near, float far)
{
	float tanHalfFovy = tan(fov / 2);

	data[0][0] = 1 / (aspectRatio * tanHalfFovy);
	data[1][1] = 1 / (tanHalfFovy);
	data[2][2] = -(far + near) / (far - near);
	data[2][3] = -1;
	data[3][2] = -(2 * far * near) / (far - near);

	return;
}

void agl::Mat4f::ortho(float left, float right, float bottom, float top, float near, float far)
{
	data[0][0] = 2 / (right - left);
	data[1][1] = 2 / (top - bottom);
	data[2][2] = -2 / (far - near);
	data[3][0] = -(right + left) / (right - left);
	data[3][1] = -(top + bottom) / (top - bottom);
	data[3][2] = -(far + near) / (far - near);
	data[3][3] = 1;

	return;
}
