#version 330 core
out vec4 FragColor;
in vec3 TexCoord;
uniform sampler2D texturelol[16];
//uniform sampler2D texture2;
uniform vec3 lightPos;
in vec3 pos;
in vec3 FragPos;
in vec3 ec_pos;
//frog vars
in vec4 viewSpace;
const vec3 fogColor = vec3(1.0, 1.0, 1.0);
const float FogDistFactor = 0.012;
const float FogDensity = 0.01;
void main()
{
    float fogDist = 0;
    float fogFactor = 0;
    fogDist = length(viewSpace);
    fogDist = exp(fogDist * FogDistFactor);
    fogFactor = 1.0 / exp(fogDist * FogDensity);
    fogFactor = clamp(fogFactor, 0, 1.0);
    vec3 Normal = normalize(cross(dFdx(ec_pos), dFdy(ec_pos)));
    //vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = vec3((diff * vec3(1,1,1)));
    vec3 ambiant = vec3((vec3(0.7,0.7,0.7)));
    //FragColor = vec4(mix(fogColor, texture(texturelol[int(TexCoord.z)], TexCoord.xy).rgb, fogFactor) * (diffuse/3 + ambiant), 1);
	FragColor = vec4(texture(texturelol[int(TexCoord.z)], TexCoord.xy).rgb * (diffuse/3 + ambiant), 1);
    //FragColor = vec4(0.5,0.3,0.3,0.5) * (diffuse + ambiant);
}
