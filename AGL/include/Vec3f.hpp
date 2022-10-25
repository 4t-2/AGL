#pragma once

#include <ostream>

namespace agl
{
	class Vec3f
	{
		public:
			float x = 0;
			float y = 0;
			float z = 0;

			Vec3f				 operator-(Vec3f vector);
			friend std::ostream &operator<<(std::ostream &os, const Vec3f &vec)
			{
				char output[31];

				sprintf(output, "%+08f %+08f %+08f\n", vec.x, vec.y, vec.z);

				return os << output;
			}
	};
} // namespace agl
