#pragma once

#include <math.h>
#include <ostream>
#include <sstream>

#define PI 3.14159

namespace agl
{
	template <typename T, int max> class Vec
	{
		public:
			// \ Construct Vec to be equal to vec
			// \ &vec - vec for data to be equal to
			Vec(Vec const &vec)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] = vec.data[i];
				}
			}

			template <typename U, int amount> Vec(Vec<U, amount> const &vec)
			{
				unsigned int i;

				for (i = 0; (i < max) && (i < amount); i++)
				{
					data[i] = vec.data[i];
				}

				for (; i < max; i++)
				{
					data[i] = 0;
				}
			}

			template <typename... Ts> Vec(Ts... ts)
			{
				T *p = data;
				((*(p++) = ts), ...);
			}

			void operator=(Vec vec)
			{
				std::copy(std::begin(vec.data), std::end(vec.data), data);
			}

			void operator+=(Vec vec)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] += vec.data[i];
				}
			}

			void operator-=(Vec vec)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] -= vec.data[i];
				}
			}

			void operator*=(T scale)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] *= scale;
				}
			}

			void operator/=(T scale)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] /= scale;
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

			Vec operator+(Vec vec)
			{
				Vec newVec;

				for (int i = 0; i < max; i++)
				{
					newVec.data[i] = data[i] + vec.data[i];
				}

				return newVec;
			}

			Vec operator*(T scale)
			{
				Vec newVec;

				for (int i = 0; i < max; i++)
				{
					newVec.data[i] = data[i] * scale;
				}

				return newVec;
			}

			Vec operator/(T scale)
			{
				Vec newVec;

				for (int i = 0; i < max; i++)
				{
					newVec.data[i] = data[i] / scale;
				}

				return newVec;
			}

			bool operator==(Vec vec)
			{
				for (int i = 0; i < max; i++)
				{
					if (data[i] != vec.data[i])
					{
						return false;
					}
				}

				return true;
			}

			// \ Get length of Vec
			T length()
			{
				return sqrt(this->dot(*this));
			}

			// \ Normalize Vec
			Vec normalized()
			{
				T len = this->length();
				return {x / len, y / len, z / len};
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

			float angle()
			{
				float angle = -atan(x / y);

				if (x > 0 && y < 0)
				{
					return angle;
				}

				angle += PI;

				if (x < 0 && y < 0)
				{
					angle += PI;
				}

				return angle;
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

			union {
					T data[max] = {};
					struct
					{
							T x;
							T y;
							T z;
							T w;
					};
			};
	};

	template <typename T, typename... Ts>
	Vec(T, Ts...) -> Vec<std::enable_if_t<(std::is_same_v<T, Ts> && ...), T>, sizeof...(Ts) + 1>;
} // namespace agl
