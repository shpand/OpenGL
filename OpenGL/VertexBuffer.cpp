#include "VertexBuffer.h"
#include <GL/glew.h>
#include "Asserter.h"

VertexBuffer::VertexBuffer(const void* data, const unsigned int dataSizeInBytes)
{
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, dataSizeInBytes, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &id));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::Unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
