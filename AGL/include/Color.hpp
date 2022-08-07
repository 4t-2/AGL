#pragma once

#include "Vector4f.hpp"

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

			unsigned char	   r;
			unsigned char	   g;
			unsigned char	   b;
			unsigned char	   a;

			Vector4f toVector4f();
	};
} // namespace agl
