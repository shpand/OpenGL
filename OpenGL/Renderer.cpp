#include "Renderer.h"
#include <GL/glew.h>
#include "Asserter.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader)
{
    //Shader, Vertex array and Index buffer must be bound before drawing the shape
    //Vertex buffer may not be bound as it's already linked to Vertex Array
    shader.Bind();
    va.Bind();
    ib.Bind();
    unsigned count = ib.GetCount();
    GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}
