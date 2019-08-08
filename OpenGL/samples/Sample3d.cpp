#include "Sample3d.h"
#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp";
#include "cameras/OrthographicCamera.h"
#include "cameras/PerspectiveCamera.h"

namespace samples
{
    Sample3d::Sample3d()
    {
        shader.reset(new Shader("Basic.shader"));
        shader->Bind();
        //TODO:
        //1. Implement Camera Debug info (rotation degrees, current pos etc.)
        //4. Add GameObject that will have its own model matrix with scale, rotation and pos
        //5. Implement camera rotation AROUND object
        //6. Implement object rotation AROUND itself, not around world/view space
        //7. Use GameObject as base class for Cube etc.
        texture = new Texture("resources/textures/cube.png");
        const int textureSlot = 0;
        texture->Bind(textureSlot);
        shader->SetUniform1i("u_Texture", textureSlot);

        cubeRenderers = Sample3d::GenerateCubes(30);

        //camera = new open_gl_engine::cameras::OrthographicCamera(0.f, 1920.0f, 0.f, 1080.f, -1000.0f, 1000.0f);
        camera = new open_gl_engine::cameras::PerspectiveCamera(1920.0f, 1080.f, 45.0f, 0.1f, 10000.0f);
    }


    Sample3d::~Sample3d()
    {
    }

    void Sample3d::OnUpdate(float deltaTime, GLFWwindow* window)
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

        //model = glm::rotate(model, glm::radians((float)((int)rotateDegree % 360)), glm::vec3(1.f, 1.f, 1.f));
        glm::mat4 modelViewProjection = camera->GetViewProjectionMatrix() * glm::mat4(1.0f);
        shader->SetUniformMat4f("u_MVP", modelViewProjection);
    }

    void Sample3d::OnRender()
    {
        /* wipe the drawing surface clear */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);

        for (auto i = 0; i < cubeRenderers->size(); i++)
        {
            CubeRenderer r = cubeRenderers->at(i);
            r.Draw();
        }
    }

    std::vector<CubeRenderer>* Sample3d::GenerateCubes(const int n)
    {
        const auto cubeRenderers = new std::vector<CubeRenderer>();

        for (auto i = 0; i < n; i++)
        {
            CubeRenderer cubeRenderer(GenerateRandomPosition(), glm::vec3(30, 30, 30), shader.get());
            cubeRenderers->push_back(cubeRenderer);
        }

        return cubeRenderers;
    }

    glm::vec3 Sample3d::GenerateRandomPosition()
    {
        int x = rand() % 1920;
        int y = rand() % 1080;
        //float z = (((rand() % 100) - 50.f) / 100.f) * 2.f;
        float z = rand() % 1000;

        return glm::vec3(x, y, z);
    }
}
