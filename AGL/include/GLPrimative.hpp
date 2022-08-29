#pragma once

namespace agl
{
	class GLPrimative
	{
		private:
			int			 mode;
			unsigned int vertexBuffer;
			unsigned int colorBuffer;
			int			 vertexDataSize;
			int			 colorDataSize;

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

			void setVertexData(float vertexBufferData[], int size);
			void setColorData(float colorBufferData[], int size);

			void destroy();

			int getMode();

			unsigned int getVertexBuffer();
			int			 getVertexDataSize();
			unsigned int getColorBuffer();
			int			 getColorDataSize();
	};
} // namespace agl
