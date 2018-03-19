#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexcolor;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;


out vec3 texcoord;
out vec3 vc;

uniform mat4 V;
uniform mat4 P;

uniform mat4 ModelScale;
uniform mat4 ModelRotate;
uniform mat4 ModelTranslate;

uniform vec3 LightPosition_worldspace;
uniform sampler2D DiffuseTextureSampler;

mat4 MVP;
mat4 M;

void main(){

	M = ModelTranslate * ModelRotate * ModelScale;
	MVP = P * V * M;
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

	vc = vertexcolor;
	texcoord = vec3(vertexPosition_modelspace.xyz) /3;

}
