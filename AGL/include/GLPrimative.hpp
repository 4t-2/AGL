#pragma once

#include "Vector3f.hpp"

namespace agl
{
	class GLPrimative
	{
		private:
			unsigned int vertexBuffer;
			int			 mode;
			int			 vertices;

		public:
			/*
			\ Sets the type of primative GLPrimative will be
			\ Can be
			\ GL_POINTS
			\ GL_LINE_STRIP
			\ GL_LINE_LOOP
			\ GL_LINES
			\ GL_LINE_STRIP_ADJACENCY
			\ GL_LINES_ADJACENCY
			\ GL_TRIANGLE_STRIP
			\ GL_TRIANGLE_FAN
			\ GL_TRIANGLES
			\ GL_TRIANGLE_STRIP_ADJACENCY
			\ GL_TRIANGLES_ADJACENCY
			\ GL_PATCHES
			*/
			void setMode(int mode);

			void setVertices(Vector3f *vertex, int size);

			void destroy();

			int			 getMode();
			unsigned int getVertexBuffer();
			int			 getVertices();
	};
} // namespace agl
