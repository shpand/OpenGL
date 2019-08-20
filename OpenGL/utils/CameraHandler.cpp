#include "CameraHandler.h"
#include <glm/vec3.hpp>


utils::CameraHandler::CameraHandler() {}

utils::CameraHandler::~CameraHandler() {}

void utils::CameraHandler::UpdatePosition(float deltaTime, GLFWwindow *window, open_gl_engine::cameras::Camera *camera)
{
    static const float moveSpeed = 100.f;
    static const float rotateSpeed = 50.f;
    const glm::vec3 cameraPos = camera->GetPosition();

    if (glfwGetKey(window, GLFW_KEY_LEFT)) {
        glm::vec3 newPos = cameraPos + glm::vec3(-moveSpeed * deltaTime, 0.f, 0);
        camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
        glm::vec3 newPos = cameraPos + glm::vec3(moveSpeed * deltaTime, 0.f, 0);
        camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP)) {
        glm::vec3 newPos = cameraPos + glm::vec3(0.0f, moveSpeed * deltaTime, 0);
        camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN)) {
        glm::vec3 newPos = cameraPos + glm::vec3(0.0f, -moveSpeed * deltaTime, 0);
        camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_UP)) {
        glm::vec3 newPos = cameraPos + glm::vec3(0.0f, 0, moveSpeed * deltaTime);
        camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        glm::vec3 newPos = cameraPos + glm::vec3(0.0f, 0, -moveSpeed * deltaTime);
        camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_W)) {
        float rotation = camera->GetRotationX();
        rotation += rotateSpeed * deltaTime;
        camera->SetRotationX(rotation);
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        float rotation = camera->GetRotationX();
        rotation -= rotateSpeed * deltaTime;
        camera->SetRotationX(rotation);
    }
    if (glfwGetKey(window, GLFW_KEY_Q)) {
        float rotation = camera->GetRotationZ();
        rotation -= rotateSpeed * deltaTime;
        camera->SetRotationZ(rotation);
    }
    if (glfwGetKey(window, GLFW_KEY_E)) {
        float rotation = camera->GetRotationZ();
        rotation += rotateSpeed * deltaTime;
        camera->SetRotationZ(rotation);
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        float rotation = camera->GetRotationY();
        rotation -= rotateSpeed * deltaTime;
        camera->SetRotationY(rotation);
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        float rotation = camera->GetRotationY();
        rotation += rotateSpeed * deltaTime;
        camera->SetRotationY(rotation);
    }
}