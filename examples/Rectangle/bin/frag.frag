#version 330 core

in vec2 UVcoord;
in vec4 fragColor;
out vec4 color;

uniform sampler2D myTextureSampler;

void main()
{
    color = fragColor * texture(myTextureSampler, UVcoord);
}
