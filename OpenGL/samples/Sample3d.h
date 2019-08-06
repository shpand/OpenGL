#pragma once
#include "Sample.h"
#include "Shader.h"
#include "../renderers/CubeRenderer.h"
#include "Renderer.h"
#include "Texture.h"
#include "cameras/Camera.h"

namespace samples
{
    class Sample3d : public samples::Sample
    {
    public:
        Sample3d();
        ~Sample3d();
        void OnUpdate(float deltaTime, GLFWwindow* window) override;
        void OnRender() override;

    private:
        std::vector<CubeRenderer>* GenerateCubes(const int n);
        static glm::vec3 GenerateRandomPosition();

        open_gl_engine::cameras::Camera* camera;

        Texture* texture;

        std::vector<CubeRenderer>* cubeRenderers;
        std::unique_ptr<Shader> shader;
    };    
}

