#pragma once

#include "Vector3f.hpp"
#include <GL/gl.h>

namespace agl
{
	class GLTriangle
	{
		private:
			GLfloat vertexBufferData[9];
			GLuint	vertexBuffer;

		public:
			void setVertices(Vector3f vertex[3]);
			void setVertices(Vector3f vertex1, Vector3f vertex2, Vector3f vertex3);

			GLfloat *getVertexBufferData()
			{
				return vertexBufferData;
			};
			GLfloat getVertexBuffer()
			{
				return vertexBuffer;
			};
	};
} // namespace agl
