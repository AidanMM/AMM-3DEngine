#version 330
in vec3 Position_b;
in vec3 UV_b;
in vec3 Color_b;

uniform mat4 MVP;

out vec2 UV;
out vec3 v3Color;

void main()
{
	gl_Position = MVP * vec4(Position_b, 1);
	v3Color = Color_b;
	UV = UV_b.xy;
}