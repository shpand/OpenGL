#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexColor;

uniform mat4 u_MVP;

out vec3 fragmentColor;

void main()
{
    gl_Position = u_MVP * position;
    fragmentColor = vertexColor;
}


#shader fragment
#version 410 core

layout(location = 0) out vec3 color;

in vec3 fragmentColor;

void main()
{
    color = fragmentColor;
}