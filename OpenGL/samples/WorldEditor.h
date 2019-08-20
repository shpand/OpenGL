#pragma once
#include "Sample.h"
#include "Shader.h"
#include "cameras/Camera.h"

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

        std::unique_ptr<Shader> shader;
        std::shared_ptr<open_gl_engine::cameras::Camera> camera;
    };
}

