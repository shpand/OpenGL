#include "CubeRenderer.h"
#include "Renderer.h"
#include "../shapes/Cube.h"


CubeRenderer::CubeRenderer(const glm::vec3 centerPosition, const glm::vec3 size, Shader* shader)
: centerPosition(centerPosition), size(size), shader(shader)
{
    Cube* cube = new Cube(centerPosition.x, centerPosition.y, centerPosition.z, size.x, size.y, size.z);
    points = cube->GetPoints();//TODO: points get removed from memory in the constructor end and null pointer occurs after drawing
    indices = cube->GetIndicies();

    //TODO: delete cube?

    /* a vertex buffer object (VBO) is created here. this stores an array of
    data on the graphics adapter's memory. in our case - the vertex points */
    const int pointsSizeInBytes = points.size() * sizeof(GLfloat);
    vb = new VertexBuffer(&points[0], pointsSizeInBytes);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);//layout for texture coordinates

    va = new VertexArray();
    va->AddBuffer(*vb, layout);
    //binding of indices must happen right after vb and va has been bound.
    ib = new IndexBuffer ( &indices[0], indices.size() );
}


CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::Draw()
{
    Renderer renderer;
    renderer.Draw(*va, *ib, *shader);
}
