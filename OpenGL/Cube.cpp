#include "Cube.h"
#include <GL/glew.h>


Cube::Cube(float centerX, float centerY, float centerZ, float width, float height, float depth)
{
    
}


Cube::~Cube()
{
}

std::vector<GLfloat> Cube::GetPoints()
{
    return _points;
}

std::vector<GLfloat> Cube::GetIndicies()
{
    return _indicies;
}
