#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace open_gl_engine
{
    namespace cameras
    {
        PerspectiveCamera::PerspectiveCamera(float width, float height, float fov, float near, float far)
        {
            m_ProjectionMatrix = glm::perspective(glm::radians(fov), width / height, near, far);
            m_ViewMatrix = glm::mat4(1.0f);

            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }
    }
}