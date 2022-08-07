#pragma once

#include "Vector2f.hpp"
#include "Vector4f.hpp"

namespace agl
{
	class RectangleShape
	{
		private:
			Vector2f position;
			Vector2f size;
			Vector4f color;

		public:
			void setPosition(Vector2f position);
			void setSize(Vector2f size);
			void setColor(Vector4f color);

			Vector2f getSize();
			Vector2f getPosition();
	};
} // namespace agl
