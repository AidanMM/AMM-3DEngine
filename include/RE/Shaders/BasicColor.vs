#version 330

layout (location = 0) in vec3 Position_b;
layout (location = 1) in vec3 Color_b;

uniform mat4 MVP;
uniform int nElements = 0;
uniform mat4 mToWorldArray[250];

out vec3 Color;

void main()
{
	if( nElements < 1 )
		gl_Position = MVP * vec4(Position_b, 1);
	else
		gl_Position = (MVP * mToWorldArray[gl_InstanceID]) * vec4(Position_b, 1);
	
	Color = Color_b;
}