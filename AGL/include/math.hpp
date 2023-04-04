#pragma once

#include "Vec.hpp"
#include <math.h>

#define PI 3.14159

namespace agl
{
	// \ Get the cross product between two Vecs
	// \ a - Vec 1
	// \ b - Vec 2
	Vec<float, 3> cross(Vec<float, 3> a, Vec<float, 3> b);

	// \ Return a normalized vector that points in that angle on a circle
	// \ angle - radian vector points at
	Vec<float, 2> pointOnCircle(float angle);

	// \ Converts degrees to radians
	// \ angle - degrees to convert
	float		  degreeToRadian(float angle);

	// \ Converts radians to degrees
	// \ angle - radians to convert
	float		  radianToDegree(float angle);
} // namespace agl
