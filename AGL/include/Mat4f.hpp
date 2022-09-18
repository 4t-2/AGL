#pragma once

#include "Vec3f.hpp"
#include "Vec4f.hpp"

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

			void identity();
			void translate(Vec3f vector);
			void scale(Vec3f vector);
			void rotate(Vec3f vector);

			Mat4f multiply(Mat4f matrix);
			Vec4f multiply(Vec4f vector);
	};
} // namespace agl
