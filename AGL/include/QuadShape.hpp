#pragma once

#include "Vector3f.hpp"

namespace agl
{
	class QuadShape
	{
		private:
			Vector2f point1;
			Vector2f point2;
			Vector2f point3;
			Vector2f point4;

		public:
			void setVertexPositions(Vector3f vertex1, );
	};
} // namespace agl
