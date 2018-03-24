#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
in vec3 pos;

void main()
{
	/*if (pos.y <= 2)
	{
		FragColor = vec4(0.1,0.2,0.7,1);
	}
	else if (pos.y > 70)
	{
			FragColor = vec4(0.9,1,0.9,1);
	} else*/
		FragColor = texture(texture1, TexCoord);
    	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.1);
	//FragColor = vec4(1,0,0,1);



}
