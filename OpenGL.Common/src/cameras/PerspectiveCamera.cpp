#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace open_gl_engine
{
    namespace cameras
    {
        PerspectiveCamera::PerspectiveCamera(float width, float height, float fov, float near, float far)
        {
            m_ProjectionMatrix = glm::perspective(glm::radians(fov), width / height, near, far);
            //TODO: need to accept initial pos from method params and remember them?
            m_ViewMatrix = glm::lookAt(
                glm::vec3(0, 0, -5000), // Camera is at (0,0,5), in World Space
                glm::vec3(0, 0, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
            );

            SetPosition(m_ViewMatrix[3]);
            //How to extract rotation?

            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }
    }
}