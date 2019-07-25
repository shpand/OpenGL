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

uniform sampler2D u_Texture; //location of our texture

void main()
{
    color = texture(u_Texture, v_TexCoord).rgb;
}