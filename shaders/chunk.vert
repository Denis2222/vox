#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
out vec3 pos;
out vec3 FragPos;
out vec3 ec_pos;
out vec4 viewSpace;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    pos = aPos;
    FragPos = vec3(model * vec4(aPos, 1.0));
    ec_pos = (projection * view * model *  vec4(aPos, 1.0)).xyz;
    viewSpace = model * view * vec4(aPos, 1.0);
}
