#version 330 core

out vec4 outColor;
in vec2 fragTextureCoords;
uniform sampler2D fragTexture;

void main()
{
   outColor = texture(fragTexture, fragTextureCoords);
}
