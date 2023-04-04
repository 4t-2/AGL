#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Shader.hpp"

int agl::Shader::loadFromFile(const std::string &vertex_file_path, const std::string &fragment_file_path)
{
	std::fstream vertStream(vertex_file_path, std::ios::in);
	std::fstream fragStream(fragment_file_path, std::ios::in);

	std::string vertSrc;
	std::string fragSrc;

	if (!vertStream.good() || !fragStream.good())
	{
		return 1;
	}

	std::string line;

	while (std::getline(vertStream, line))
	{
		vertSrc += line + '\n';
	}

	while (std::getline(fragStream, line))
	{
		fragSrc += line + '\n';
	}

	return this->compileSrc(vertSrc, fragSrc);
}

int agl::Shader::compileSrc(std::string &vertSrc, std::string &fragSrc)
{
	int exitCode = 0;

	// Create the shaders
	GLuint VertexShaderID	= glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int	  InfoLogLength;

	// Compile Vertex Shader
	char const *VertexSourcePointer = vertSrc.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char *VertexShaderErrorMessage = (char *)malloc(InfoLogLength + 1);

		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);

		printf("%s\n", VertexShaderErrorMessage);
		exitCode = 2;

		free(VertexShaderErrorMessage);
	}

	// Compile Fragment Shader
	char const *FragmentSourcePointer = fragSrc.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char *FragmentShaderErrorMessage = (char *)malloc(InfoLogLength + 1);

		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

		printf("%s\n", FragmentShaderErrorMessage);
		exitCode = 2;

		free(FragmentShaderErrorMessage);
	}

	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char *ProgramErrorMessage = (char *)malloc(InfoLogLength + 1);

		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);

		printf("%s\n", ProgramErrorMessage);
		exitCode = 2;

		free(ProgramErrorMessage);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	this->programID = ProgramID;

	return exitCode;
}

void agl::Shader::use()
{
	glUseProgram(programID);

	return;
}

void agl::Shader::deleteProgram()
{
	glDeleteProgram(programID);

	return;
}

GLuint agl::Shader::getProgramID()
{
	return programID;
}

int agl::Shader::getUniformLocation(const char *name)
{
	return glGetUniformLocation(programID, name);
}

void agl::Shader::setUniformMatrix4fv(GLuint location, Mat4f matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.data[0][0]);

	return;
}

void setUniformVector2fv(GLuint location, agl::Vec<float, 2> vector)
{
	glUniform2f(location, vector.x, vector.y);

	return;
}

void agl::Shader::setUniformVector3fv(GLuint location, Vec<float, 3> vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);

	return;
}
