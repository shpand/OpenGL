#pragma once
#include <GLFW/glfw3.h>
#include "cameras/Camera.h"

namespace utils
{
    class CameraHandler
    {
    public:
        CameraHandler();
        ~CameraHandler();

        void UpdatePosition(float deltaTime, GLFWwindow* window, open_gl_engine::cameras::Camera *camera);
    };
}
