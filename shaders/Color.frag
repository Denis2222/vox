#version 330 core

// Interpolated values from the vertex shaders

in vec3 texcoord;
in vec3 vc;
out vec3 color;

uniform mat4 ModelScale;
uniform mat4 ModelRotate;
uniform mat4 ModelTranslate;
uniform sampler2D DiffuseTextureSampler;

uniform float RatioColorTexture;

mat4 M;


void main()
{
	color = vc * RatioColorTexture;
	color += texture(DiffuseTextureSampler, texcoord.zy *3).rgb * (1 - RatioColorTexture);
}
