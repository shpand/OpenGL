#pragma once
#include "Camera.h"

namespace open_gl_engine
{
    namespace cameras
    {
        class OrthographicCamera : public Camera
        {
        public:
            OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

        };
    }
}

