#pragma once

#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Vec2f.hpp"
#include "Vec3f.hpp"
#include "Texture.hpp"

namespace agl
{
	class Shape
	{
		protected:
			Vec3f position = {0, 0, 0};
			Vec3f size	   = {1, 1, 1};
			Vec3f rotation = {0, 0, 0};
			Color color	   = {255, 0, 0, 0};

			GLPrimative shapeData;
			int textureID = 0;

		public:
			~Shape();

			void setPosition(Vec3f position);
			void setPosition(Vec2f position);
			void setSize(Vec3f size);
			void setSize(Vec2f size);
			void setRotation(Vec3f rotation);
			void setRotation(Vec2f rotation);
			void setColor(Color color);

			void setTexture(Texture *texture);

			Vec3f getPosition();
			Vec3f getSize();
			Vec3f getRotation();
			Color getColor();
			int getTextureID();

			void		setShapeData();
			GLPrimative getShapeData();
	};
} // namespace agl
