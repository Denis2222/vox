#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
in vec3 pos;

void main()
{
	if (pos.y <= 15)
	{
		FragColor = vec4(0,0,1,1);
	}
	else if (pos.y > 30)
	{
			FragColor = vec4(1,1,1,1);
	} else
    	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.1);
	//FragColor = vec4(1,0,0,1);



}
