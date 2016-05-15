#version 330
uniform sampler2D TextureID;

in vec2 UV;
in vec3 v3Color;

out vec4 Fragment;

void main()
{
	Fragment = vec4(0,0,0,0);
	vec4 v4Color = texture( TextureID, UV );
	if(v4Color.w != 0)
	{
		Fragment = v4Color * vec4(v3Color, 1);
	}
	
	return;
}