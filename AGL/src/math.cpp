#include "../include/math.hpp"

agl::Vec<float, 3> agl::cross(agl::Vec<float, 3> a, agl::Vec<float, 3> b)
{
	return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

agl::Vec<float, 2> agl::pointOnCircle(float angle)
{
	return {cos(angle), sin(angle)};
}

float agl::degreeToRadian(float angle)
{
	return angle * PI / 180;
}

float agl::radianToDegree(float angle)
{
	return angle * 180 / PI;
}
