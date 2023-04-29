#pragma once

#include "external.hpp"

namespace agl
{
	class GLPrimative
	{
		private:
			int mode;

			int			  bufferAmount;
			int			  vertexAmount;
			int			 *vertexSize;
			unsigned int *buffer;

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

			void genBuffers(int amount);
			void setVertexAmount(int amount);
			void setBufferData(int index, float bufferData[], int vertexSize);

			void deleteData();

			int			 getMode();
			int			 getBufferAmount();
			int			 getVertexAmount();
			int			 getVertexSize(int index);
			unsigned int getBuffer(int index);
	};
} // namespace agl
