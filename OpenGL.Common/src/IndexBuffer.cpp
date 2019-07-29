#include "IndexBuffer.h"
#include <GL/glew.h>
#include "utils/Asserter.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :count(count)
{
    //indicesSizeInBytes - how many bytes (values/points) we want to get from the start of data
    const int indicesSizeInBytes = count * sizeof(GLuint);
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeInBytes, data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &id));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
