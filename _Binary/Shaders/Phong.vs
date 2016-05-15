#version 330
layout (location = 0) in vec3 Position_b;
layout (location = 1) in vec3 Color_b;
layout (location = 2) in vec3 UV_b;
layout (location = 3) in vec3 Normal_b;
layout (location = 4) in vec3 Binormal_b;
layout (location = 5) in vec3 Tangent_b;

uniform mat4 MVP;
uniform int nElements;
uniform mat4 m4ToWorld[250];

uniform vec3 LightPosition_W;
uniform vec3 CameraPosition_W;

out VS_OUT
{
	vec3 Position;
	vec2 UV;
	vec3 Color;
	vec3 Normal;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
}vs_out;

void main()
{
	gl_Position = MVP * m4ToWorld[gl_InstanceID] * vec4(Position_b, 1.0);
	vs_out.Position = vec3(m4ToWorld[gl_InstanceID] * vec4(Position_b, 1.0));
	vs_out.Color = Color_b;
	vs_out.UV = vec2(UV_b);
	
	mat3 normalMatrix = transpose(inverse(mat3(m4ToWorld[gl_InstanceID])));

	vec3 T = normalize(normalMatrix * Tangent_b);
	vec3 B = normalize(normalMatrix * Binormal_b);
	vec3 N = normalize(normalMatrix * Normal_b);
	
	mat3 TBN = mat3(T, B, N);
	
	vs_out.Normal = TBN * Normal_b;
	vs_out.TangentLightPos = TBN * LightPosition_W;
	vs_out.TangentViewPos = TBN * CameraPosition_W;
	vs_out.TangentFragPos = TBN * vs_out.Position;
}