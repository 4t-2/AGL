#pragma once

#include "Mat4f.hpp"
#include "external.hpp"
#include "ShaderBuilder.hpp"

namespace agl
{
	class Shader
	{
		private:
			GLuint programID;
			GLuint matrixID;

		public:
			// \ load a vertex and fragment shader from files
			// \ vertex_file_path - file path of vertex shader
			// \ fragment_file_path - file path of fragment shader
			// \ Returns
			// \ 0 - Success
			// \ 1 - File(s) not found
			// \ 2 - Other error
			int loadFromFile(const std::string &vertex_file_path, const std::string &fragment_file_path);

			int compileSrc(std::string &vertSrc, std::string &fragSrc);

			// \ Use the shader
			void use();

			// \ Get location of a uniform in the shader
			// \ name - name of the uniform
			// \ Returns the location of the uniform
			int getUniformLocation(const char *name);

			// \ Sets the value of a matrix uniform
			// \ location - location of uniform
			// \ matrix - value to set uniform to
			static void setUniformMatrix4fv(GLuint location, Mat4f matrix);

			// \ Sets the value of a vector uniform
			// \ location - location of uniform
			// \ vector - value to set uniform to
			static void setUniformVector3fv(GLuint location, Vec<float, 3> vector);

			static void setUniformVector2fv(GLuint location, Vec<float, 2> vector);

			// \ Delete shader
			void deleteProgram();

			// \ Get the ID of the shader program
			// \ Returns the ID of the program
			GLuint getProgramID();
	};
} // namespace agl
