#version 330
uniform int nTexture = 0;
uniform sampler2D TextureID;
uniform sampler2D NormalID;
uniform sampler2D SpecularID;
uniform vec3 LightPosition_W;

uniform vec3 Tint;

uniform vec3 AmbientColor;
uniform float AmbientPower;

uniform vec3 LightColor;
uniform float LightPower;
uniform vec3 CameraPosition;

in vec3 Normal_W;
in vec3 Tangent_W;
in vec3 Binormal_W;
in vec3 Position_W;
in vec3 Eye_W;
in vec2 UV;
in vec3 Color;

out vec4 Fragment;

vec4 MaterialDiffuseColor = vec4( 0, 0, 0, 1);
vec4 MaterialAmbientColor = vec4( 0, 0, 0, 1);
vec4 MaterialSpecularColor = vec4( 0, 0, 0, 1);
vec3 LightDirection = vec3( 0, 0, 0);
float attenuationFactor;
bool ComputeDiffuseAndAmbient()
{
	if( nTexture == 1 || nTexture == 3 || nTexture == 5 || nTexture == 7 )
	{
		MaterialDiffuseColor = texture( TextureID, UV );
		
		float newColor = MaterialDiffuseColor.x + MaterialDiffuseColor.y + MaterialDiffuseColor.z;
		newColor = newColor / 3.0;
		MaterialDiffuseColor = vec4(newColor, newColor, newColor, MaterialDiffuseColor.w);

		if(MaterialDiffuseColor.w == 0)
		{
			return false;
		}
	}
	else
	{
		MaterialDiffuseColor = vec4(Color, 1);
	}

    if(Tint.x != -1 && Tint.y != -1 && Tint.z != -1)
            MaterialDiffuseColor = MaterialDiffuseColor * vec4(Tint, 1);

	MaterialAmbientColor = vec4(AmbientColor, 1) * MaterialDiffuseColor * AmbientPower;
	return true;
}
void ComputeSpecular()
{
	if(nTexture == 4 || nTexture == 5 || nTexture == 6 || nTexture == 7)
	{
		MaterialSpecularColor = texture( SpecularID, UV );
	}
	else
	{
		MaterialSpecularColor = vec4( 1.0, 1.0, 1.0, 1.0);
	}
}

vec3 ComputeNormal()
{
	// -- Light Calculation
	vec3 Normal;
	if(nTexture == 2 || nTexture == 3 || nTexture == 6 || nTexture == 7)
	{
		vec3 BumpMap = texture( NormalID, UV ).rgb;
		Normal = (BumpMap * 2.0) - vec3(1.0,1.0,1.0);//In tangent space
		//mat3 TBN = mat3( Tangent_W, Binormal_W, Normal_W); //Matrix that translates from tangent to world
		//Normal = TBN * Normal; //Normal in World coordinates;
		Normal = Normal_W + Normal.x * Tangent_W + Normal.y * Binormal_W + Normal.z;
	}
	else
	{
		Normal = Normal_W;	
	}

	Normal = normalize(Normal);
	return Normal;
}
vec4 ComputeDiffuseLight(vec3 Normal)
{
	LightDirection = LightPosition_W - Position_W;
	float distance = length(LightDirection);
	attenuationFactor = 1.0 / (distance * distance);
	LightDirection = normalize(LightDirection);

	float DiffuseFactor = clamp( dot(Normal, LightDirection), 0.0, 1.0);
	vec3 Computation = LightColor * LightPower * DiffuseFactor * attenuationFactor;
	return vec4(Computation, 1);
}
vec4 ComputeSpecularLight(vec3 Normal)
{
	vec3 VertexToEye = normalize(Eye_W - Position_W);
	vec3 LightReflect = normalize(reflect(-LightDirection, Normal));
	float SpecularFactor = clamp( dot( VertexToEye, LightReflect ), 0, 1 );
	vec3 Computation = LightColor * LightPower * pow(SpecularFactor, 5) * attenuationFactor;
	return vec4(Computation, 1);
}
void main()
{
	if(ComputeDiffuseAndAmbient() == false)
	{
		Fragment = vec4( 1, 1, 1, 0);
		return;
	}
	ComputeSpecular();
	vec3 Normal = ComputeNormal();

	vec4 Diffuse = ComputeDiffuseLight(Normal);
	MaterialDiffuseColor = MaterialDiffuseColor * Diffuse;
	
	vec4 Specular = ComputeSpecularLight(Normal);
	MaterialSpecularColor = MaterialSpecularColor * Specular;

	Fragment = MaterialAmbientColor + MaterialSpecularColor + MaterialDiffuseColor;

    return;
}