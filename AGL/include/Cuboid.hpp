#pragma once

#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Vec3f.hpp"

namespace agl
{
	class Cuboid
	{
		private:
			agl::GLPrimative shape;
		public:
			void setSizePosition(Vec3f size, Vec3f position);
			void setColor(Color color);

			void deleteData();

			GLPrimative getShape();
	};
}
