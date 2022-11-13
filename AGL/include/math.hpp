#pragma once

#include "Vec.hpp"
#include <math.h>

#define PI 3.14159

namespace agl
{
	Vec<float, 3> cross(Vec<float, 3> a, Vec<float, 3> b);
	Vec<float, 2> pointOnCircle(float angle);
	float		  degreeToRadian(float angle);
	float		  radianToDegree(float angle);
} // namespace agl
