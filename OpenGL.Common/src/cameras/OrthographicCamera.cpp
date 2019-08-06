#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace open_gl_engine
{
    namespace cameras
    {
        OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
            : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, near, far)), m_ViewMatrix(1.0f)
        {
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }

        void OrthographicCamera::RecalculateViewMatrix()
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

            m_ViewMatrix = glm::inverse(transform);
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }

    }
}