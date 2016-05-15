#version 330
uniform int nTexture = 0;
uniform sampler2D TextureID;

in vec2 UV;
in vec3 Color;

uniform vec3 Tint;

out vec4 Fragment;

void main()
{
	if( nTexture == 1 || nTexture == 3 || nTexture == 5 || nTexture == 7 )
	{
		Fragment = texture( TextureID, UV );
	}
	else
	{
		Fragment = vec4(Color,1);
	}

	return;
}