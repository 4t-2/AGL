#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Vec2f.hpp"
#include <GL/gl.h>

namespace agl
{
	class Circle
	{
		private:
			float radius;
			Vec2f position;
			Color color;
			GLPrimative shape;
			float *vertexData;
			unsigned int faces;

		public:
			Circle(unsigned int faces);
			// ~Circle();

			void setRadius(float radius);
			void setPosition(Vec2f position);
			void setColor(Color color);

			void setData();
			void deleteData();

			GLPrimative getShape();
	};
}
