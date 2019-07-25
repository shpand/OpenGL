#pragma once
#include <GL/glew.h>
#include <vector>

class Square
{
public:
    //TODO: add glm::vec3
    Square(float centerX, float centerY, float width, float height);
    ~Square();

    std::vector<GLfloat> GetPoints();
    std::vector<unsigned> GetIndicies();

private:
    static std::vector<GLfloat> CalculatePoints(float centerX, float centerY, float width, float height);
    static std::vector<GLfloat> CalculatePointsWithUV(float centerX, float centerY, float width, float height);
    std::vector<GLfloat> CalculatePointsWithColor(float centerX, float centerY, float width, float height);

    std::vector<GLfloat> _points;
    std::vector<unsigned> _indicies
    {
        0, 1, 2,
        2, 3, 0
    };
};

