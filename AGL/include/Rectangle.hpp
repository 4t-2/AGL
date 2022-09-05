#pragma once

#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Vec2f.hpp"

namespace agl
{
	class Rectangle
	{
			agl::GLPrimative shape;

			Vec2f size	   = {0, 0};
			Vec2f position = {0, 0};
			Color color	   = {0, 0, 0, 0};

		public:
			void setSize(Vec2f size);
			void setPosition(Vec2f position);
			void setColor(Color color);

			void setData();
			void deleteData();

			GLPrimative getShape();
	};
} // namespace agl
