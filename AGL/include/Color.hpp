#pragma once

#include "Vec.hpp"

namespace agl
{
	class Color
	{
		public:
			static const Color Red;
			static const Color Green;
			static const Color Blue;

			static const Color Cyan;
			static const Color Magenta;
			static const Color Yellow;

			static const Color White;
			static const Color Black;
			static const Color Gray;

			unsigned char r = 0;
			unsigned char g = 0;
			unsigned char b = 0;
			unsigned char a = 0;

			agl::Vec<float, 3> normalized();
	};
} // namespace agl
