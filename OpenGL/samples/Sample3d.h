#pragma once
#include "Sample.h"
#include "Shader.h"
#include "../renderers/CubeRenderer.h"
#include "Renderer.h"
#include "Texture.h"

namespace samples
{
    class Sample3d : public samples::Sample
    {
    public:
        Sample3d();
        ~Sample3d();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;

    private:
        std::vector<CubeRenderer>* GenerateCubes(const int n);
        static glm::vec3 GenerateRandomPosition();

        float offsetX = 0;
        float rotateDegree = 0;
        float mover;
        glm::mat4 projection;
        glm::mat4 viewMatrix;

        Texture* texture;

        std::vector<CubeRenderer>* cubeRenderers;
        std::unique_ptr<Shader> shader;
    };    
}

