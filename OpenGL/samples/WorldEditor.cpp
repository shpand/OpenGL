#include "WorldEditor.h"
#include "VertexArray.h"
#include "cameras/PerspectiveCamera.h"
#include "../constants/ScreenParams.h"
#include "../utils/CameraHandler.h"

namespace samples
{

    WorldEditor::WorldEditor()
    {
        shader.reset(new Shader("Basic.shader"));
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", glm::mat4(1.f));

        camera.reset(new open_gl_engine::cameras::PerspectiveCamera(screen_params::Width, screen_params::Height, 45, 0.1f, 1000));
        camera->SetPosition({ 0, 20, 20 });
        camera->SetRotationX(-45);
    }


    WorldEditor::~WorldEditor()
    {
    }

    void samples::WorldEditor::OnUpdate(float deltaTime, GLFWwindow* window)
    {
        UpdateCamera(deltaTime, window);

        glm::mat4 modelViewProjection = camera->GetViewProjectionMatrix() * glm::mat4(1.0f);
        shader->SetUniformMat4f("u_MVP", modelViewProjection);
    }

    void samples::WorldEditor::OnRender()
    {
        //TODO: add camera that looks from above. Draw lines along Z and X
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.4f, 0.4f, 0.4f, 0);

        DrawWorldGrid();
    }

    void samples::WorldEditor::UpdateCamera(float deltaTime, GLFWwindow* window)
    {
        utils::CameraHandler cameraHandler;
        cameraHandler.UpdatePosition(deltaTime, window, camera.get());
    }

    void WorldEditor::DrawWorldGrid()
    {
        //TODO: reduce draw calls
        for(int x = -50; x < 51; x++)
        {
            float zCoord = x * 10;
            std::vector<GLfloat> horizontalLinePoints =
            {
                -static_cast<float>(screen_params::Width) / 2, 0, zCoord,
                static_cast<float>(screen_params::Width) / 2, 0, zCoord
            };

            VertexBuffer vb = VertexBuffer(&horizontalLinePoints[0], horizontalLinePoints.size() * sizeof(float));

            VertexBufferLayout layout;
            layout.Push<float>(3);

            VertexArray va = VertexArray();
            va.AddBuffer(vb, layout);

            glDrawArrays(GL_LINES, 0, horizontalLinePoints.size());

            float xCoord = x * 10;
            std::vector<GLfloat> verticalLinePoints =
            {
                xCoord, 0, -static_cast<float>(screen_params::Height) / 2,
                xCoord, 0, static_cast<float>(screen_params::Height) / 2
            };

            VertexBuffer vb2 = VertexBuffer(&verticalLinePoints[0], verticalLinePoints.size() * sizeof(float));

            VertexBufferLayout layout2;
            layout2.Push<float>(3);

            VertexArray va2 = VertexArray();
            va2.AddBuffer(vb2, layout2);

            glDrawArrays(GL_LINES, 0, verticalLinePoints.size());
        }
    }
}
