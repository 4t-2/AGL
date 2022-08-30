#pragma once

#include "Color.hpp"
#include "Vec2f.hpp"

namespace agl
{
	class Rectangle
	{
		private:
			Vec2f size;
			Vec2f position;
			Color  color;

		public:
			void setSize(Vec2f size);
			void setPosition(Vec2f position);
			void setColor(Color color);

			Vec2f getSize();
			Vec2f getPosition();
			Color getColor();
	};
} // namespace agl
