#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 Normal_cameraspace;

//ADD FOR Normal map
in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;

out vec3 color;

uniform sampler2D DiffuseTextureSampler;
uniform sampler2D NormalTextureSampler;
uniform sampler2D SpecularTextureSampler;

uniform vec3 LightPosition_worldspace;



void main()
{
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 50.0f;

	vec3 MaterialDiffuseColor = texture( DiffuseTextureSampler, UV ).rgb;
	vec3 MaterialAmbientColor = vec3(0.5,0.5,0.5) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = texture( SpecularTextureSampler, UV ).rgb * 0.3;

	// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS) for better quality
	vec3 TextureNormal_tangentspace = normalize(texture( NormalTextureSampler, vec2(UV.x,UV.y) ).rgb*2.0 - 1.0);

	float distance = length( LightPosition_worldspace - Position_worldspace );



vec3 n = TextureNormal_tangentspace;
vec3 l = normalize(LightDirection_tangentspace);

/*
	vec3 n = normalize( Normal_cameraspace );
	vec3 l = normalize( LightDirection_cameraspace );
	*/
	float cosTheta = clamp( dot( n,l ), 0,1 );

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);

	//color = texture( SpecularTextureSampler, UV ).rgb;
	//	color.xyz = vec3(1,0,0);
}
