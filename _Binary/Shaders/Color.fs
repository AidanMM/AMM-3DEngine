#version 330

uniform vec3 Color;
uniform vec3 Tint;

out vec4 Fragment;

void main()
{
	Fragment = vec4(Color,1);
    if(Tint.x != -1 && Tint.y != -1 && Tint.z != -1)
    //    Fragment = Fragment * vec4(Tint, 1);
		
	Fragment = vec4(Color,1);

	return;
}