#pragma once

#include <ostream>
#include <sstream>

namespace agl
{
	template <typename T = float, int max = 4> class Vec
	{
		public:
			Vec()
			{
				for (unsigned int i = 0; i < size; i++)
				{
					data[i] = 0;
				}
			}

			Vec(Vec const &vec)
			{
				for (unsigned int i = 0; i < max; i++)
				{
					data[i] = vec.data[i];
				}
			}

			Vec(T x, T y, T z, T w)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}

			Vec(T x, T y, T z)
			{
				this->x = x;
				this->y = y;
				this->z = z;
			}

			Vec(T x, T y)
			{
				this->x = x;
				this->y = y;
			}

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

			friend std::ostream &operator<<(std::ostream &os, const Vec &vec)
			{
				std::stringstream output;

				for (int i = 0; i < max-1; i++)
				{
					output << vec.data[i] << " ";
				}
					
				output << vec.data[max-1];

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
