#pragma once

#include "Shape.hpp"
#include <vector>

namespace agl
{
	// \ only use it with <agl::RenderWindow&>
	// \ agl::RenderWindow::draw() wont work otherwise
	template <typename T> class _Drawable
	{
		public:
			virtual void drawFunction(T)
			{
			}
	};
} // namespace agl
