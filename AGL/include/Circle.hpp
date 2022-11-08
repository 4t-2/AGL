#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Shape.hpp"
#include <GL/gl.h>

namespace agl
{
	class Circle : public Shape
	{
		private:

		public:
			Circle(unsigned int faces);
	};
}
