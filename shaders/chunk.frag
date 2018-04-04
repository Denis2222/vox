#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 lightPos;

in vec3 VertPos;


in vec3 pos;

in vec3 FragPos;
in vec3 ec_pos;

void main()
{

	vec3 Normal = normalize(cross(dFdx(ec_pos), dFdy(ec_pos)));

	//vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(Normal, lightDir), 0.0);

	vec4 diffuse = vec4((diff * vec3(1,1,1)), 1);
	vec4 ambiant = vec4((vec3(0.7,0.7,0.7)), 1);

	FragColor = texture(texture1, TexCoord) * (diffuse/3 + ambiant);
	//FragColor = vec4(0.5,0.3,0.3,0.5) * (diffuse + ambiant);
}
