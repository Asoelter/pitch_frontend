#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 vertTextureCoords;

out vec2 fragTextureCoords;

uniform float offset;

void main()
{
    vec4 position = vec4(pos.x + offset, pos.yz, 1.0);
    gl_Position = position;
    fragTextureCoords = vertTextureCoords;
}
