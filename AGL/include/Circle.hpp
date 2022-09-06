#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Vec2f.hpp"
namespace agl
{
	class Circle
	{
		private:
			float radius;
			Vec2f position;
			Color color;
			GLPrimative shape;
		public:
			Circle(int points);

			void setRadius(float radius);
			void setPosition(Vec2f position);
			void setColor(Color color);

			void setData();
			void deleteData();

			GLPrimative getShape();
	};
}
