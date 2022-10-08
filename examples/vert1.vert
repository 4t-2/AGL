#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;
uniform vec3 vec3Color;

out vec2 UV;
out vec3 fragColor;

void main()
{
    UV = vertexUV;
	fragColor = vec3Color;

    gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);
}
