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

			Vec3f size	   = {0, 0, 0};
			Vec3f position = {0, 0, 0};
			Color color	   = {0, 0, 0};

		public:
			void setSize(Vec3f size);
			void setPosition(Vec3f position);
			void setColor(Color color);

			void setData();
			void deleteData();

			GLPrimative getShape();
	};
} // namespace agl
