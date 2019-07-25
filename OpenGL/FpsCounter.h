#pragma once
#include <GLFW/glfw3.h>

class FpsCounter
{
public:
    FpsCounter(GLFWwindow *window);
    ~FpsCounter();

    void Update();

private:
    GLFWwindow *window;
};

