#version 330

in vec3 Color;

out vec4 Fragment;

uniform vec3 WireColor = vec3(-1,-1,-1);

void main()
{
	if(WireColor.z != -1 )
		Fragment = vec4(WireColor,1);
	else
		Fragment = vec4(Color,1);
	

	return;
}