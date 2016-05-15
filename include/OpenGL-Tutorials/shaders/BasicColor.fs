#version 330

in vec3 Color;

out vec4 Fragment;

void main()
{
	Fragment = vec4(Color,1);

	return;
}