#pragma once

#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Vec2f.hpp"
#include "Vec3f.hpp"

namespace agl
{
	class Shape
	{
		protected:
			Vec3f position = {0, 0, 0};
			Vec3f size	   = {1, 1, 1};
			Color color	   = {1, 0, 0, 0};

			GLPrimative shapeData;
			float	   *vertexData;
			float	   *colorData;

		public:
			~Shape();

			void setPosition(Vec3f position);
			void setPosition(Vec2f position);
			void setSize(Vec3f size);
			void setSize(Vec2f size);
			void setColor(Color color);

			void setShapeData();
			GLPrimative getShapeData();

	};
} // namespace agl
