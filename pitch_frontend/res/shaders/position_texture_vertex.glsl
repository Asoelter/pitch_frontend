#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 vertTextureCoords;

out vec2 fragTextureCoords;

uniform mat4 rotation;
uniform mat4 view = mat4(1.0, 0.0, 0.0, 0.0,
                         0.0, 1.0, 0.0, 0.0,
                         0.0, 0.0, 1.0, 0.0,
                         0.0, 0.0, 0.0, 1.0);
uniform mat4 projection = mat4(1.0, 0.0, 0.0, 0.0,
                               0.0, 1.0, 0.0, 0.0,
                               0.0, 0.0, 1.0, 0.0,
                               0.0, 0.0, 0.0, 1.0);

void main()
{
    gl_Position = projection * view * rotation* vec4(pos, 1.0);
    fragTextureCoords = vertTextureCoords;
}
