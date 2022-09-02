#pragma once

#include <GL/glew.h>

#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>

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
			int	 loadFromFile(const char *vertex_file_path, const char *fragment_file_path);
			void setUniformMatrix4fv(GLuint MatrixID, const GLfloat *MPV);
			void remove();

			GLuint getProgramID();
	};
} // namespace agl
