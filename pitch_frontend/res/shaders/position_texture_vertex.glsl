#version 330 core

const mat4 identity = mat4(1.0, 0.0, 0.0, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0);

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 vertTextureCoords;

out vec2 fragTextureCoords;

uniform mat4 model      = identity;
uniform mat4 view       = identity;
uniform mat4 projection = identity;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    fragTextureCoords = vertTextureCoords;
}
