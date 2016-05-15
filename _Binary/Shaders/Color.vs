#version 330

layout (location = 0) in vec3 Position_b;

uniform mat4 MVP;
uniform int nElements;
uniform mat4 m4ToWorld[250];

void main()
{
	if( nElements < 1 )
	{
		gl_Position = MVP * vec4(Position_b, 1);
	}
	else
	{
		gl_Position = (MVP * m4ToWorld[gl_InstanceID]) * vec4(Position_b, 1);
	}
}