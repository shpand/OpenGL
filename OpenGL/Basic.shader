#shader vertex
#version 410 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

out vec4 o_position;

void main()
{
    gl_Position = u_MVP * position;
    o_position = gl_Position;
}


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec4 o_position;

void main()
{
    color = o_position;
}