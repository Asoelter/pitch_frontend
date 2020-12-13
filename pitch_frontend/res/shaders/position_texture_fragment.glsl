#version 330 core

out vec4 outColor;
in vec2 fragTextureCoords;

uniform sampler2D fragTexture;

void main()
{
	vec4 testColor = texture(fragTexture, fragTextureCoords);

	if(testColor.a < 0.01)
	{
		discard;
	}

	outColor = testColor;
}
