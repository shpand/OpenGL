#pragma once
#include "Sample.h"
#include "Shader.h"
#include "cameras/Camera.h"

#include <memory>

namespace samples
{
    class WorldEditor : public samples::Sample
    {
    public:
        WorldEditor();
        ~WorldEditor();
        void OnUpdate(float deltaTime, GLFWwindow* window) override;
        void OnRender() override;

    private:
        void UpdateCamera(float deltaTime, GLFWwindow* window);
        void DrawSkyGradient();
        void DrawWorldGrid();

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Shader> skyShader;
        std::shared_ptr<open_gl_engine::cameras::Camera> camera;
    };
}

