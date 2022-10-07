#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;
uniform vec3 VecColor;

out vec2 UV;
out vec3 vecC;

void main()
{
    UV = vertexUV;
	vecC = VecColor;

    gl_Position = MVP * vec4(position.x, position.y, VecColor.z, 1.0);
}
