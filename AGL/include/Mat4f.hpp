#pragma once

#include "Vec3f.hpp"
#include "Vec4f.hpp"
#include <cstddef>

namespace agl
{
	class Mat4f
	{
		public:
			float data[4][4] = {
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0},
			};

			Mat4f operator*(Mat4f matrix);
			Vec4f operator*(Vec4f vector);
			
			void clear();

			void identity();
			void translate(Vec3f vector);
			void scale(Vec3f vector);
			void rotate(Vec3f vector);
	};
} // namespace agl
