#pragma once

namespace agl
{
	class GLPrimative
	{
		private:
			int			 mode;
			unsigned int vertexBuffer;
			unsigned int colorBuffer;
			int			 bufferSize;

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

			void genVertexBuffer();
			void genColorBuffer();

			// size - Number of bytes
			void setBufferSize(int size);

			void setVertexData(float vertexBufferData[]);
			void setColorData(float colorBufferData[]);

			void deleteData();

			int getMode();

			unsigned int getVertexBuffer();
			int			 getBufferSize();
			unsigned int getColorBuffer();
	};
} // namespace agl
