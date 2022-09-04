#pragma once

#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Vec2f.hpp"

namespace agl
{
	class Rectangle
	{
		agl::GLPrimative shape;

		public:
			void setSizePosition(Vec2f size, Vec2f position);
			void setColor(Color color);

			void deleteData();

			GLPrimative getShape();
	};
} // namespace agl
