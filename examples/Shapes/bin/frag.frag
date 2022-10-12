#version 330 core

in vec2 UV;
in vec3 shapeColor;
out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{
    color = shapeColor * texture(myTextureSampler, UV).rgb;
}
