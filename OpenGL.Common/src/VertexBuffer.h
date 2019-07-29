#pragma once
class VertexBuffer
{
private:
    unsigned int id;
public:
    VertexBuffer(const void* data, unsigned int dataSizeInBytes);
    ~VertexBuffer();

    void Bind() const;
    static void Unbind();
};

