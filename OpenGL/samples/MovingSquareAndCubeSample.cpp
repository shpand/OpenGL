#include "MovingSquareAndCubeSample.h"
#include "../shapes/Square.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp";
#include "../renderers/CubeRenderer.h"

namespace samples
{
    MovingSquareAndCubeSample::MovingSquareAndCubeSample()
    {
        Square* square = new Square(-0.5, -0.5, 0.5, 1);
        std::vector<GLfloat> points2 = square->GetPoints();
        std::vector<unsigned int> indices2 = square->GetIndicies();

        //Prepare 2nd cube-----------------------------------------------------------
        const int pointsSizeInBytes2 = points2.size() * sizeof(GLfloat);
        VertexBuffer vb2(&points2[0], pointsSizeInBytes2);

        VertexBufferLayout layout2;
        layout2.Push<float>(2);
        layout2.Push<float>(2); //layout for texture coordinates

        va2 = new VertexArray();
        va2->AddBuffer(vb2, layout2);

        ib2 = new IndexBuffer(&indices2[0], indices2.size());
        //End of preparing 2nd cube---------------------------------------------------


        /* here we copy the shader strings into GL shaders, and compile them. we
        then create an executable shader 'program' and attach both of the compiled
                shaders. we link this, which matches the outputs of the vertex shader to
        the inputs of the fragment shader, etc. and it is then ready to use */

        shader = new Shader("Basic.shader");
        //Shader shader("color.shader");
        shader->Bind();

        texture = new Texture("resources/textures/cube.png");
        const int textureSlot = 0;
        texture->Bind(textureSlot);
        shader->SetUniform1i("u_Texture", textureSlot);

        /* this loop clears the drawing surface, then draws the geometry described
                by the VAO onto the drawing surface. we 'poll events' to see if the window
        was closed, etc. finally, we 'swap the buffers' which displays our drawing
                surface onto the view area. we use a double-buffering system which means
                that we have a 'currently displayed' surface, and 'currently being drawn'
                surface. hence the 'swap' idea. in a single-buffering system we would see
                stuff being drawn one-after-the-other */

        cubeRenderer = new CubeRenderer(glm::vec3(0.5, 0.5, 0), glm::vec3(0.5, 0.5, 0.5), shader);


        projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0, 0)); //it's essentially a camera that we move

        mover = 0.0004;
    }


    MovingSquareAndCubeSample::~MovingSquareAndCubeSample()
    {
        //TODO: free resources
    }

    void MovingSquareAndCubeSample::OnUpdate(float deltaTime, GLFWwindow* window)
    {
        offsetX += mover;
        rotateDegree += mover;
        if (offsetX > 1)
        {
            offsetX = 1;
            mover = -mover;
        }
        else if (offsetX < -1)
        {
            offsetX = -1;
            mover = -mover;
        }
        glm::vec3 translationX(offsetX, 0, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationX);//objects transformation
        model = glm::rotate(model, glm::radians(rotateDegree * 90), glm::vec3(1.f, 1.f, 1.f));
        glm::mat4 modelViewProjection = projection * viewMatrix * model;
        shader->SetUniformMat4f("u_MVP", modelViewProjection);
    }

    void MovingSquareAndCubeSample::OnRender()
    {
        /* wipe the drawing surface clear */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);

        cubeRenderer->Draw();
        renderer.Draw(*va2, *ib2, *shader);
    }
}
