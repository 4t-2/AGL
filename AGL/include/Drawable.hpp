#pragma once

#include "Shape.hpp"
#include <vector>

namespace agl
{
	// \ only use it with <agl::RenderWindow&>
	// \ agl::RenderWindow::draw() wont work otherwise
	template <typename T> class Drawable
	{
		protected:
			std::function<void(T)> drawFunction;

		public:
			void setDrawFunction(std::function<void(T)> drawFunction)
			{
				this->drawFunction = drawFunction;
			}

			std::function<void(T)> getDrawFunction()
			{
				return drawFunction;
			}
	};
} // namespace agl
