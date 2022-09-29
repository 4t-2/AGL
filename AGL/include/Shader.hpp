#pragma once

#include "external.hpp"

namespace agl
{
	class Shader
	{
		private:
			GLuint	programID;
			GLuint	matrixID;

		public:
			/*
			\ 0 - Success
			\ 1 - File(s) not found
			\ 2 - Other error
			*/
			int	 loadFromFile(const char *vertex_file_path, const char *fragment_file_path);
			// void setCamera(Camera &camera);
			// void updateCamera();

			void use();
			int getUniformLocation(const char *name);
			static void setUniformMatrix4fv(GLuint MatrixID, const GLfloat *matrix);
			void deleteProgram();

			GLuint getProgramID();
	};
} // namespace agl
