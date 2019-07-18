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
    std::vector<int> GetIndicies();

private:
    static std::vector<GLfloat> CalculatePoints(float centerX, float centerY, float centerZ, float width, float height, float depth);

    std::vector<GLfloat> _points;
    std::vector<int> _indicies
    {
        0,1,2,
        2,3,0,
        0,3,4,
        4,7,0,
        0,1,6,
        6,7,0,
        5,6,1,
        1,2,5,
        5,2,3,
        3,4,5,
        5,6,7,
        7,4,5
    };
};

