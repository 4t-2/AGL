#version 330 core

in vec2 UV;
in vec3 vecC;
out vec3 color;

void main()
{
    color = vecC;
}
