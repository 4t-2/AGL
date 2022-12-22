#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;

uniform mat4 transform;
uniform mat4 mvp;
uniform vec3 shapeColor;

out vec2 UVcoord;
out vec4 fragColor;

void main()
{
    UVcoord = vertexUV;

	fragColor = vec4(shapeColor, 1);

    gl_Position = mvp * transform * vec4(position, 1);
}

