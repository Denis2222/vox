#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;


float near = 0.1;
float far  = 2000.0;


float LinearizeDepth(float depth)
{
  float z = depth * 2.0 - 1.0; // back to NDC
  return (2.0 * near * far) / (far + near - z * (far - near));
}


void main()
{
    //FragColor = texture(texture_diffuse1, TexCoords);
	FragColor = texture(texture_diffuse1, TexCoords) / (gl_FragCoord.z*10);
	//float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
	//    FragColor = vec4(vec3(depth), 1.0);
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}
