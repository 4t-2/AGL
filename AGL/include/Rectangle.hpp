#pragma once

#include "Color.hpp"
#include "Float2.hpp"

namespace agl
{
	class Rectangle
	{
		private:
			Float2 size;
			Float2 position;
			Color  color;

		public:
			void setSize(Float2 size);
			void setPosition(Float2 position);
			void setColor(Color color);

			Float2 getSize();
			Float2 getPosition();
			Color getColor();
	};
} // namespace agl
