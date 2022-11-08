#pragma once

#include "Vec.hpp"
#include <cstdio>
#include <iostream>

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
			Vec<float, 4> operator*(Vec<float, 4> vector);

			friend std::ostream &operator<<(std::ostream &os, const Mat4f &mat)
			{
				char output[161];

				sprintf(output,
						"%+08f %+08f %+08f %+08f\n"											//
						"%+08f %+08f %+08f %+08f\n"											//
						"%+08f %+08f %+08f %+08f\n"											//
						"%+08f %+08f %+08f %+08f\n",										//
						mat.data[0][0], mat.data[1][0], mat.data[2][0], mat.data[3][0], //
						mat.data[0][1], mat.data[1][1], mat.data[2][1], mat.data[3][1], //
						mat.data[0][2], mat.data[1][2], mat.data[2][2], mat.data[3][2], //
						mat.data[0][3], mat.data[1][3], mat.data[2][3], mat.data[3][3]	//
				);

				return os << output;
			}

			void clear();

			void identity();
			void translate(Vec<float, 3> translation);
			void scale(Vec<float, 3> scale);
			void rotate(Vec<float, 3> rotation);
			void rotateX(float x);
			void rotateY(float y);
			void rotateZ(float z);

			void perspective(float fov, float aspectRatio, float near, float far);
			void ortho(float left, float right, float bottom, float top, float near, float far);
			void lookAt(Vec<float, 3> pos, Vec<float, 3> target, Vec<float, 3> head);
	};
} // namespace agl
