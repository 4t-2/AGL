#pragma once

#include <math.h>
#include <ostream>
#include <sstream>

namespace agl
{
	template <typename T = float, int max = 4> class Vec
	{
		public:
			// \ Construct Vec with data starting all at 0
			Vec()
			{
				for (unsigned int i = 0; i < size; i++)
				{
					data[i] = 0;
				}
			}

			// \ Construct Vec to be equal to vec
			// \ &vec - vec for data to be equal to
			Vec(Vec const &vec)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] = vec.data[i];
				}
			}

			// \ Construct Vec to xyzw values
			// \ x - X value
			// \ y - Y value
			// \ z - Z value
			// \ w - W value
			Vec(T x, T y, T z, T w)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}

			// \ Construct Vec to xyz values
			// \ x - X value
			// \ y - Y value
			// \ z - Z value
			Vec(T x, T y, T z)
			{
				this->x = x;
				this->y = y;
				this->z = z;
			}

			// \ Construct Vec to xy values
			// \ x - X value
			// \ y - Y value
			Vec(T x, T y)
			{
				this->x = x;
				this->y = y;
			}

			// \ Construct Vec to x value
			// \ x - X value
			Vec(T x)
			{
				this->x = x;
			}

			void operator=(Vec vec)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] = vec.data[i];
				}
			}

			Vec operator-(Vec vec)
			{
				Vec newVec;

				for (int i = 0; i < max; i++)
				{
					newVec.data[i] = data[i] - vec.data[i];
				}

				return newVec;
			}

			// \ Get length of Vec
			T length()
			{
				return sqrt(this->dot(*this));
			}

			// \ Normalize Vec
			Vec normalize()
			{
				T len = this->length();
				return {x /= len, y /= len, z /= len};
			}

			// \ Get the dot product of Vec and vec
			// \ vec - second vector
			float dot(Vec vec)
			{
				float dot = 0;

				for (int i = 0; i < size; i++)
				{
					dot += data[i] * vec.data[i];
				}

				return dot;
			}

			friend std::ostream &operator<<(std::ostream &os, const Vec &vec)
			{
				std::stringstream output;

				for (int i = 0; i < max - 1; i++)
				{
					output << vec.data[i] << " ";
				}

				output << vec.data[max - 1];

				return os << output.str();
			}

			const unsigned int size = max;

			T data[max];

			T &x = data[0];
			T &y = data[1];
			T &z = data[2];
			T &w = data[3];
	};
} // namespace agl
