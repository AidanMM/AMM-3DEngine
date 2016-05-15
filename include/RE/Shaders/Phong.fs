#version 330
in VS_OUT
{
	vec3 Position;
	vec2 UV;
	vec3 Color;
	vec3 Normal;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
}fs_in;

uniform vec3 AmbientColor;
uniform float AmbientPower;

uniform vec3 LightColor;
uniform float LightPower;

uniform int nTexture = 0;
uniform sampler2D TextureID;
uniform sampler2D NormalID;
uniform sampler2D SpecularID;

out vec4 Fragment;

void main()
{
	//Basic coloring
	vec4 v4Color = vec4(fs_in.Color, 1);
	vec3 ambient = AmbientColor * AmbientPower;
	
	//DiffuseMap
	if( nTexture == 1 || nTexture == 3 || nTexture == 5 || nTexture == 7 )
	{
		vec4 v4DiffuseT = texture( TextureID, fs_in.UV );
		if(v4DiffuseT.w == 0)//Alpha == 0
		{
			Fragment = vec4(0,0,0,0);
			return;
		}
		v4Color = v4DiffuseT;
	}
	
	//Normal
	vec3 normal = normalize(fs_in.Normal);
	//NormalMap
	if(nTexture == 2 || nTexture == 3 || nTexture == 6 || nTexture == 7)
	{
		vec4 NormalMap = texture( NormalID, fs_in.UV );
		if(NormalMap.w != 0)//If texture loaded
		{
			normal = normalize(vec3(NormalMap) * 2.0 - 1.0);//Tangent space
		}
	}
	
	//Diffuse
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * v4Color.rgb;
	
	//Specular
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	vec3 specular = (LightColor * LightPower) * spec;
		
	//SpecularMap
	if(nTexture == 4 || nTexture == 5 || nTexture == 6 || nTexture == 7)
	{
		vec4 specularT = texture( SpecularID, fs_in.UV );
		if(specularT.w != 0)//If texture loaded
		{
			specular = vec3(specular * vec3(specularT));
		}
	}
	Fragment = vec4(ambient + diffuse + specular, 1.0);
	
	return;
}