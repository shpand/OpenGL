#include "WorldEditor.h"
#include "VertexArray.h"

namespace samples
{

    WorldEditor::WorldEditor()
    {
        shader.reset(new Shader("Basic.shader"));
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", glm::mat4(1.f));
    }


    WorldEditor::~WorldEditor()
    {
    }

    void samples::WorldEditor::OnUpdate(float deltaTime, GLFWwindow* window)
    {
    }

    void samples::WorldEditor::OnRender()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.4f, 0.4f, 0.4f, 0);

        std::vector<GLfloat> points =
        {
            std::numeric_limits<float>::min(), 0, 0,
            std::numeric_limits<float>::max(), 0, 0
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
