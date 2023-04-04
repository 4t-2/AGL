#version 330 core

in vec2 UVcoord;
in vec4 fragColor;

out vec4 color;

uniform sampler2D textureSampler;
uniform vec2 UVpos;
uniform vec2 UVsca;

void main()
{
    color = texture(textureSampler, UVcoord) * fragColor;
}
