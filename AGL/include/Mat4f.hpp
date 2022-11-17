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

			// \ Zero all the values
			void clear();

			// \ Set Mat4f to an identity matrix
			void identity();

			// \ Set Mat4f to a translation matrix
			// \ translation - how to translate
			void translate(Vec<float, 3> translation);

			// \ Set Mat4f to scaling matrix
			// \ scale - how to scale
			void scale(Vec<float, 3> scale);

			// \ Set Mat4f to an XYZ rotation matrix
			// \ rotation - how to rotate
			void rotate(Vec<float, 3> rotation);

			// \ Set Mat4f to an X rotation matrix
			// \ x - how to rotate
			void rotateX(float x);

			// \ Set Mat4f to an Y rotation matrix
			// \ y - how to rotate
			void rotateY(float y);

			// \ Set Mat4f to an Z rotation matrix
			// \ z - how to rotate
			void rotateZ(float z);

			// \ Set Mat4f to a perspective transformation matrix
			// \ fov - FOV
			// \ aspectRatio - aspect ration
			// \ near - distance until an object is too near to see
			// \ far - distance until an object is too far to see
			void perspective(float fov, float aspectRatio, float near, float far);

			// \ Set Mat4f to an orthographic transformation matrix
			// \ left - value of far left
			// \ right - value of far right
			// \ bottom - value of far bottom
			// \ top - value of far top
			// \ near - distance until an object is too near to see
			// \ far - distance until an object is too far to see
			void ortho(float left, float right, float bottom, float top, float near, float far);

			// \ Set Mat4f to look at a certain point while in a certain position
			// \ pos - position of the camera
			// \ target - position of the target
			// \ head - direction that the top of the camera is pointing
			void lookAt(Vec<float, 3> pos, Vec<float, 3> target, Vec<float, 3> head);
	};
} // namespace agl
