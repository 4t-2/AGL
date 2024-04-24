#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Shader.hpp"

GLuint compileShader(std::string &src, GLuint glType)
{
	GLuint id = glCreateShader(glType);

	char const *ccp = src.c_str();

	glShaderSource(id, 1, &ccp, NULL);
	glCompileShader(id);

	GLint result;
	int	  logLength;

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		char *errorMsg = (char *)malloc(logLength + 1);

		glGetShaderInfoLog(id, logLength, NULL, &errorMsg[0]);

		std::cout << errorMsg << '\n';

		free(errorMsg);
	}

	return id;
}

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
	GLuint VertexShaderID	= compileShader(vertSrc, GL_VERTEX_SHADER);
	GLuint FragmentShaderID = compileShader(fragSrc, GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int	  InfoLogLength;

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

int agl::Shader::v2loadFromFile(const std::string &vertex_file_path, const std::string &fragment_file_path,
								const std::string &geometry_file_path)
{
	std::fstream vertStream(vertex_file_path, std::ios::in);
	std::fstream fragStream(fragment_file_path, std::ios::in);
	std::fstream geomStream(geometry_file_path, std::ios::in);

	std::string vertSrc;
	std::string fragSrc;
	std::string geomSrc;

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

	while (std::getline(geomStream, line))
	{
		geomSrc += line + '\n';
	}

	int exitCode = 0;

	// Create the shaders
	GLuint VertexShaderID	= compileShader(vertSrc, GL_VERTEX_SHADER);
	GLuint FragmentShaderID = compileShader(fragSrc, GL_FRAGMENT_SHADER);
	GLuint GeometryShaderID = compileShader(geomSrc, GL_GEOMETRY_SHADER);

	GLint Result = GL_FALSE;
	int	  InfoLogLength;

	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glAttachShader(ProgramID, GeometryShaderID);
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
	glDetachShader(ProgramID, GeometryShaderID);

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

template <> void agl::Shader::setUniform<agl::Mat4f>(GLuint location, agl::Mat4f matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.data[0][0]);
}

template <> void agl::Shader::setUniform<agl::Vec<float, 2>>(GLuint location, agl::Vec<float, 2> vector)
{
	glUniform2f(location, vector.x, vector.y);
}

template <> void agl::Shader::setUniform<agl::Vec<float, 3>>(GLuint location, agl::Vec<float, 3> vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}
