#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertColor;

out vec3 vecColor;

void main()
{
	vecColor = vertColor;
    gl_Position = vec4(position, 1);
}
