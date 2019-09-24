#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_MVP;

out vec2 v_TexCoord;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
}


#shader fragment
#version 410 core

layout(location = 0) out vec3 color;

in vec2 v_TexCoord;

uniform sampler2D texture_diffuse1; //location of our texture
uniform sampler2D texture_diffuse2; //location of our texture
uniform sampler2D texture_specular1; //location of our texture
uniform sampler2D texture_specular2; //location of our texture

void main()
{
    color = texture(texture_diffuse1, v_TexCoord).rgb;
}