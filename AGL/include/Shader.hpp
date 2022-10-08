#pragma once

#include "Mat4f.hpp"
#include "external.hpp"

#include "Vec3f.hpp"

namespace agl
{
	class Shader
	{
		private:
			GLuint programID;
			GLuint matrixID;

		public:
			/*
			\ 0 - Success
			\ 1 - File(s) not found
			\ 2 - Other error
			*/
			int loadFromFile(const char *vertex_file_path, const char *fragment_file_path);
			// void setCamera(Camera &camera);
			// void updateCamera();

			void		use();
			int			getUniformLocation(const char *name);
			static void setUniformMatrix4fv(GLuint location, Mat4f matrix);
			static void setUniformVector3fv(GLuint location, Vec3f vector);
			void		deleteProgram();

			GLuint getProgramID();
	};
} // namespace agl
