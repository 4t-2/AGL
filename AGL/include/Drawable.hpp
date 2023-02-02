#pragma once

#include "Shape.hpp"
#include <vector>

namespace agl
{
	class Drawable
	{
		protected:
			std::vector<agl::Shape *> shape;

		public:
			std::vector<agl::Shape *> &getShape();
	};
} // namespace agl
