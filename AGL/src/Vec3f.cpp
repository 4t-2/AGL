#include "../include/Vec3f.hpp"

agl::Vec3f agl::Vec3f::operator-(Vec3f vector)
{
	return {x - vector.x, y - vector.y, z - vector.z};
}
