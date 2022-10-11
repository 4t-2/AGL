#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;

uniform mat4 Transform;
uniform mat4 MVP;

out vec2 UV;

void main()
{
    UV = vertexUV;

    gl_Position = MVP * Transform * vec4(position, 1);
}
