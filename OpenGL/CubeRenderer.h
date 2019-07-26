#pragma once

#include "vendor/glm/vec3.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class CubeRenderer
{
public:
    CubeRenderer(glm::vec3 centerPosition, glm::vec3 size, Shader* shader);
    ~CubeRenderer();

    void Draw();

private:
    glm::vec3 centerPosition;
    glm::vec3 size;
    VertexBuffer* vb;
    VertexArray* va;
    IndexBuffer* ib;
    Shader* shader;
    std::vector<GLfloat> points;
    std::vector<unsigned> indices;
};

