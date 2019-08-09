#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>

namespace open_gl_engine
{
    namespace cameras
    {

        Camera::Camera()
        {
        }


        Camera::~Camera()
        {
        }

        void Camera::RecalculateViewMatrix()
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationX), glm::vec3(1, 0, 0)) *
                    glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationY), glm::vec3(0, 1, 0)) *
                        glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationZ), glm::vec3(0, 0, 1));

            m_ViewMatrix = glm::inverse(transform);
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

            printf("Camera position: %f, %f, %f\n", m_Position.x, m_Position.y, m_Position.z);
            printf("Camera rotation: %f, %f, %f\n", m_RotationX, m_RotationY, m_RotationZ);
        }
    }
}
