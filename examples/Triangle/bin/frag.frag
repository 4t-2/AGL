#version 330 core

in vec3 vecColor;
out vec4 color;

void main()
{
    color = vec4(vecColor, 1);
}
