#pragma once
#include <GL/glew.h>
#include <vector>

class Cube
{
public:
    //TODO: add glm::vec3
    Cube(float centerX, float centerY, float centerZ, float width, float height, float depth);
    ~Cube();

    std::vector<GLfloat> GetPoints();
    std::vector<GLfloat> GetIndicies();

private:
    std::vector<GLfloat> _points;
    std::vector<GLfloat> _indicies;
};

