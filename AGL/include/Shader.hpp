#pragma once

#include "Mat4f.hpp"
#include "ShaderBuilder.hpp"
#include "external.hpp"
#include <type_traits>

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

			template <typename T> static void setUniform(GLuint location, T t);

			// \ Delete shader
			void deleteProgram();

			// \ Get the ID of the shader program
			// \ Returns the ID of the program
			GLuint getProgramID();
	};
} // namespace agl
