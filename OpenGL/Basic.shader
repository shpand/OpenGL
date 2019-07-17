#shader vertex
#version 410 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
}


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.5, 0, 0.5, 1.0);
}