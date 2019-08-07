#pragma once
#include "Camera.h"

namespace open_gl_engine
{
    namespace cameras
    {
        class PerspectiveCamera : public Camera
        {
        public:
            PerspectiveCamera(float width, float height, float fov, float near, float far);

        };
    }
}
