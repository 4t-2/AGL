#pragma once

#include "Camera.hpp"

#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>

namespace agl
{
	class Shader
	{
		private:
			GLuint	programID;
			GLuint	matrixID;
			Camera *camera;

		public:
			/*
			\ 0 - Success
			\ 1 - File(s) not found
			\ 2 - Other error
			*/
			int	 loadFromFile(const char *vertex_file_path, const char *fragment_file_path);
			
			void use();
			void setCamera(Camera &camera);
			void updateCamera();
			
			void setUniformMatrix4fv(GLuint MatrixID, const GLfloat *matrix);
			int getUniformLocation(const char *name);

			void deleteProgram();

			GLuint getProgramID();
	};
} // namespace agl
