#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace samples
{
    class Sample
    {
    public:
        Sample();
        virtual ~Sample();

        virtual void OnUpdate(float deltaTime, GLFWwindow* window);
        virtual void OnRender();
    };
}

