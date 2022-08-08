#pragma once

#include<GL/glew.h>

#include <GL/gl.h>

namespace agl
{
	class Shader
	{
		private:
			GLuint programID;
		public:
			/*
			\ 0 - Success
			\ 1 - File(s) not found
			\ 2 - Other error
			*/
			int loadShaders(const char * vertex_file_path, const char * fragment_file_path);
			void remove();

			GLuint getProgramID();
	};
}
