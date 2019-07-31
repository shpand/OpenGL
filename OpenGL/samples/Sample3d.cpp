#include "Sample3d.h"
#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp";

namespace samples
{
    Sample3d::Sample3d()
    {
        shader.reset(new Shader("Basic.shader"));
        shader->Bind();
        //TODO:
        //1. add camera
        //2. and key handlers.
        //3. Fix model rotation
        //4. Add GameObject that will have its own model matrix with scale, rotation and pos
        //5. Implement camera rotation AROUND object
        //6. Implement object rotation AROUND itself, not around world/view space
        //7. Use GameObject as base class for Cube etc.
        texture = new Texture("resources/textures/cube.png");
        const int textureSlot = 0;
        texture->Bind(textureSlot);
        shader->SetUniform1i("u_Texture", textureSlot);

        cubeRenderers = Sample3d::GenerateCubes(30);


        projection = glm::ortho<float>(0.f, 1920.0f, 0.f, 1080.f, -1000.0f, 1000.0f);
        viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0, 0)); //it's essentially a camera that we move

        mover = 0.4;
    }


    Sample3d::~Sample3d()
    {
    }

    void Sample3d::OnUpdate(float deltaTime)
    {
        offsetX += mover;
        rotateDegree += mover;
        if (offsetX > 300)
        {
            offsetX = 300;
            mover = -mover;
        }
        else if (offsetX < -300)
        {
            offsetX = -300;
            mover = -mover;
        }
        glm::vec3 translationX(offsetX, 0, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationX);//objects transformation
        model = glm::rotate(model, glm::radians((float)((int)rotateDegree % 360)), glm::vec3(1.f, 1.f, 1.f));
        glm::mat4 modelViewProjection = projection * viewMatrix * model;
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
        float z = (((rand() % 100) - 50.f) / 100.f) * 2.f;

        return glm::vec3(x, y, z);
    }
}
