#shader vertex
#version 410 core

layout(location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position, 1.0);
}


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.5, 0, 0.5, 1.0);
}