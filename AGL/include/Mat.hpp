#pragma once

#include "Vec.hpp"
#include "math.hpp"
#include <cstdio>
#include <iostream>

namespace agl
{
	template <typename T = float, int size = 4> class Mat
	{
		private:
			template <int i, int n> constexpr inline std::array<int, i> makeSequence(std::array<int, i> &a)
			{
				a[n] = n;
				if constexpr (n < i)
				{
					makeSequence<i, n + 1>(a);
				}
			}
			template <int i> constexpr inline std::array<int, i> makeSequence()
			{
				std::array<int, i> a;

				makeSequence<i, 0>(a);

				return a;
			}

		public:
			T data[size][size] = {};

			Mat operator*(Mat matrix)
			{
				Mat newMatrix;

				for (int i = 0; i < size; ++i)
				{
					for (int j = 0; j < size; ++j)
					{
						for (int k = 0; k < size; ++k)
						{
							newMatrix.data[i][j] += matrix.data[i][k] * data[k][j];
						}
					}
				}

				return newMatrix;
			}
			Vec<float, 4> operator*(Vec<float, 4> vector)
			{
				Vec<float, 4> newVector;

				newVector.x = (data[0][0] * vector.x) + (data[1][0] * vector.y) + (data[2][0] * vector.z) +
							  (data[3][0] * vector.w);
				newVector.y = (data[0][1] * vector.x) + (data[1][1] * vector.y) + (data[2][1] * vector.z) +
							  (data[3][1] * vector.w);
				newVector.z = (data[0][2] * vector.x) + (data[1][2] * vector.y) + (data[2][2] * vector.z) +
							  (data[3][2] * vector.w);
				newVector.w = (data[0][3] * vector.x) + (data[1][3] * vector.y) + (data[2][3] * vector.z) +
							  (data[3][3] * vector.w);

				return newVector;
			}

			friend std::ostream &operator<<(std::ostream &os, const Mat &mat)
			{
				char output[161];

				sprintf(output,
						"%+08f %+08f %+08f %+08f\n"										//
						"%+08f %+08f %+08f %+08f\n"										//
						"%+08f %+08f %+08f %+08f\n"										//
						"%+08f %+08f %+08f %+08f\n",									//
						mat.data[0][0], mat.data[1][0], mat.data[2][0], mat.data[3][0], //
						mat.data[0][1], mat.data[1][1], mat.data[2][1], mat.data[3][1], //
						mat.data[0][2], mat.data[1][2], mat.data[2][2], mat.data[3][2], //
						mat.data[0][3], mat.data[1][3], mat.data[2][3], mat.data[3][3]	//
				);

				return os << output;
			}

			// \ Zero all the values
			void clear()
			{
				data[0][0] = 0;
				data[1][1] = 0;
				data[2][2] = 0;
				data[3][3] = 0;
			}

			// \ Set Mat4f to an identity matrix
			void identity()
			{
				data[0][0] = 1;
				data[1][1] = 1;
				data[2][2] = 1;
				data[3][3] = 1;

				return;
			}

			// \ Set Mat4f to a translation matrix
			// \ translation - how to translate
			void translate(Vec<float, 3> translation)
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

			// \ Set Mat4f to scaling matrix
			// \ scale - how to scale
			void scale(Vec<float, 3> scale)
			{
				data[0][0] = scale.x;
				data[1][1] = scale.y;
				data[2][2] = scale.z;
				data[3][3] = 1;

				return;
			}

			// \ Set Mat4f to an XYZ rotation matrix
			// \ rotation - how to rotate
			void rotate(Vec<float, 3> rotation)
			{
				Mat rotationX;
				Mat rotationY;
				Mat rotationZ;
				Mat rotationTotal;

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

			// \ Set Mat4f to an X rotation matrix
			// \ x - how to rotate
			void rotateX(float x)
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

			// \ Set Mat4f to an Y rotation matrix
			// \ y - how to rotate
			void rotateY(float y)
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

			// \ Set Mat4f to an Z rotation matrix
			// \ z - how to rotate
			void rotateZ(float z)
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

			// \ Set Mat4f to a perspective transformation matrix
			// \ fov - FOV
			// \ aspectRatio - aspect ration
			// \ near - distance until an object is too near to see
			// \ far - distance until an object is too far to see
			void perspective(float fov, float aspectRatio, float near, float far)
			{
				float tanHalfFovy = tan(fov / 2);

				data[0][0] = 1 / (aspectRatio * tanHalfFovy);
				data[1][1] = 1 / (tanHalfFovy);
				data[2][2] = -(far + near) / (far - near);
				data[2][3] = -1;
				data[3][2] = -(2 * far * near) / (far - near);

				return;
			}

			// \ Set Mat4f to an orthographic transformation matrix
			// \ left - value of far left
			// \ right - value of far right
			// \ bottom - value of far bottom
			// \ top - value of far top
			// \ near - distance until an object is too near to see
			// \ far - distance until an object is too far to see
			void ortho(float left, float right, float bottom, float top, float near, float far)
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

			// \ Set Mat4f to look at a certain point while in a certain position
			// \ pos - position of the camera
			// \ target - position of the target
			// \ head - direction that the top of the camera is pointing
			void lookAt(Vec<float, 3> pos, Vec<float, 3> target, Vec<float, 3> head)
			{
				agl::Vec<float, 3> f = ((target - pos).normalized());
				agl::Vec<float, 3> s = (agl::cross(f, head).normalized());
				agl::Vec<float, 3> u = (agl::cross(s, f));

				data[0][0] = s.x;
				data[1][0] = s.y;
				data[2][0] = s.z;
				data[0][1] = u.x;
				data[1][1] = u.y;
				data[2][1] = u.z;
				data[0][2] = -f.x;
				data[1][2] = -f.y;
				data[2][2] = -f.z;
				data[3][0] = -s.dot(pos);
				data[3][1] = -u.dot(pos);
				data[3][2] = f.dot(pos);

				data[3][3] = 1.0f;

				return;
			}
	};

	typedef Mat<float, 4> Mat4f;
} // namespace agl
