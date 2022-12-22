#version 330 core

in vec2 UV;
in vec3 fragColor;
out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{
    color = vec3(fragColor.z, fragColor.x, fragColor.y) * texture(myTextureSampler, UV).rgb;
}

