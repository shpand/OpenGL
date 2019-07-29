#pragma once

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class Renderer
{
public:
    void Clear() const;
    void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader);

private:

};