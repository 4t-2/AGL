#include "stdio.h"
#include "stdlib.h"

#include "../include/Shader.hpp"

int agl::Shader::loadShaders(const char *vertex_file_path, const char *fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID	= glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	int size;
	int exitCode = 0;

	char *VertexShaderCode;
	FILE *VertexShaderCodeStream = fopen(vertex_file_path, "r");

	if(VertexShaderCodeStream == NULL)
	{
		return 1;
	}

	fseek(VertexShaderCodeStream, 0L, SEEK_END);
	size = ftell(VertexShaderCodeStream);
	fseek(VertexShaderCodeStream, 0L, SEEK_SET);

	VertexShaderCode = (char *)malloc(size);

	for (int i = 0; i < size; i++)
	{
		VertexShaderCode[i] = fgetc(VertexShaderCodeStream);
	}

	fclose(VertexShaderCodeStream);

	char *FragmentShaderCode;
	FILE *FragmentShaderCodeStream = fopen(fragment_file_path, "r");

	if(FragmentShaderCodeStream == NULL)
	{
		return 1;
	}
	
	fseek(FragmentShaderCodeStream, 0L, SEEK_END);
	size = ftell(FragmentShaderCodeStream);
	fseek(FragmentShaderCodeStream, 0L, SEEK_SET);

	FragmentShaderCode = (char *)malloc(size);

	for (int i = 0; i < size; i++)
	{
		FragmentShaderCode[i] = fgetc(FragmentShaderCodeStream);
	}

	fclose(FragmentShaderCodeStream);

	GLint Result = GL_FALSE;
	int	  InfoLogLength;

	// Compile Vertex Shader
	char const *VertexSourcePointer = VertexShaderCode;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char *VertexShaderErrorMessage = (char *)malloc(InfoLogLength + 1);

		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		exitCode = 2;

		free(VertexShaderErrorMessage);
	}

	// Compile Fragment Shader
	char const *FragmentSourcePointer = FragmentShaderCode;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char *FragmentShaderErrorMessage = (char *)malloc(InfoLogLength + 1);

		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
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
		exitCode = 2;

		free(ProgramErrorMessage);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	this->programID = ProgramID;

	free(FragmentShaderCode);

	return exitCode;
}

void agl::Shader::remove()
{
	glDeleteProgram(programID);

	return;
}

GLuint agl::Shader::getProgramID()
{
	return programID;
}
