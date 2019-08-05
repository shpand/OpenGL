#pragma once
#include "Sample.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "../renderers/CubeRenderer.h"

namespace samples
{
    class MovingSquareAndCubeSample : public Sample
    {
    public:
        MovingSquareAndCubeSample();
        ~MovingSquareAndCubeSample();
        void OnUpdate(float deltaTime, GLFWwindow* window) override;
        void OnRender() override;

    private:
        float offsetX = 0;
        float rotateDegree = 0;
        float mover;
        glm::mat4 projection;
        glm::mat4 viewMatrix;

        VertexArray* va2;
        IndexBuffer* ib2;
        Texture* texture;

        Renderer renderer;
        CubeRenderer* cubeRenderer;
        Shader* shader;
    };
}

