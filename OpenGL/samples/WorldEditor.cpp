#include "WorldEditor.h"
#include "VertexArray.h"
#include "cameras/PerspectiveCamera.h"
#include "../constants/ScreenParams.h"

namespace samples
{

    WorldEditor::WorldEditor()
    {
        shader.reset(new Shader("Basic.shader"));
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", glm::mat4(1.f));

        camera.reset(new open_gl_engine::cameras::PerspectiveCamera(screen_params::Width, screen_params::Height, 45, 0.1f, 1000));
        camera->SetPosition({ 0, 0, 20 });
        //camera->SetRotationY(180);
    }


    WorldEditor::~WorldEditor()
    {
    }

    void samples::WorldEditor::OnUpdate(float deltaTime, GLFWwindow* window)
    {
        glm::mat4 modelViewProjection = camera->GetViewProjectionMatrix() * glm::mat4(1.0f);
        shader->SetUniformMat4f("u_MVP", modelViewProjection);
    }

    void samples::WorldEditor::OnRender()
    {
        //TODO: add camera that looks from above. Draw lines along Z and X
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.4f, 0.4f, 0.4f, 0);

        std::vector<GLfloat> points =
        {
            0, 0, 0,
            static_cast<float>(screen_params::Width), 0, 0
        };

        VertexBuffer vb = VertexBuffer(&points[0], points.size() * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);

        VertexArray va = VertexArray();
        va.AddBuffer(vb, layout);

        glDrawArrays(GL_LINE_STRIP, 0, points.size());

        //delete vb;
        //delete va;
    }

    void samples::WorldEditor::UpdateCamera(float deltaTime, GLFWwindow* window)
    {
    }
}
