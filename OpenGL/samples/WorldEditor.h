#pragma once
#include "Sample.h"
#include "Shader.h"
#include "cameras/Camera.h"
#include <entities\Model.h>

#include <memory>
#include "../renderers/SkyBoxRenderer.h"

namespace samples
{
    class WorldEditor : public samples::Sample
    {
    public:
        WorldEditor(GLFWwindow& window);
        ~WorldEditor();
        void OnUpdate(float deltaTime, GLFWwindow* window) override;
        void OnRender() override;

		std::shared_ptr<open_gl_engine::cameras::Camera> camera;

    private:
        void UpdateCamera(float deltaTime, GLFWwindow* window);
        void DrawSkyGradient();
        void DrawSkyBox();
        void DrawWorldGrid();
		void DrawScene();

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Shader> skyShader;
		std::unique_ptr<open_gl_engine::Model> model;
		std::unique_ptr<SkyBoxRenderer> skyBoxRenderer;
    };
}

