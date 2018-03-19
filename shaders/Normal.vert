#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexcolor;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexNormal_modelspace;
layout(location = 4) in vec3 vertexTangent_modelspace;
layout(location = 5) in vec3 vertexBitangent_modelspace;


out vec2 UV;
out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 Normal_cameraspace;

out vec3 LightDirection_tangentspace;
out vec3 EyeDirection_tangentspace;

uniform mat4 V;
uniform mat4 P;

uniform mat4 ModelScale;
uniform mat4 ModelRotate;
uniform mat4 ModelTranslate;

uniform vec3 LightPosition_worldspace;


mat4 MVP;
mat3 MV3x3;
mat4 M;

void main(){
	M = ModelTranslate * ModelRotate * ModelScale;
	MV3x3 = mat3(V * M);
	MVP = P * V * M;
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

	Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;

	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz;

	UV = vertexUV;


	// ADD FOR Normal map

	vec3 vertexTangent_cameraspace = MV3x3 * vertexTangent_modelspace;
	vec3 vertexBitangent_cameraspace = MV3x3 * vertexBitangent_modelspace;
	vec3 vertexNormal_cameraspace = MV3x3 * vertexNormal_modelspace;

	mat3 TBN = transpose(mat3(
		vertexTangent_cameraspace,
		vertexBitangent_cameraspace,
		vertexNormal_cameraspace
	)); // You can use dot products instead of building this matrix and transposing it. See References for details.

	LightDirection_tangentspace = TBN * LightDirection_cameraspace;
	EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;
}
