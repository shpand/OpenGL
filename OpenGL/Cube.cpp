#include "Cube.h"
#include <GL/glew.h>


Cube::Cube(const float centerX, const float centerY, const float centerZ, const float width, const float height, const float depth)
{
    _points = CalculatePoints(centerX, centerY, centerZ, width, height, depth);
}


Cube::~Cube()
{
}

std::vector<GLfloat> Cube::GetPoints()
{
    return _points;
}

std::vector<int> Cube::GetIndicies()
{
    return _indicies;
}

std::vector<GLfloat> Cube::CalculatePoints(const float centerX, const float centerY, const float centerZ, const float width, const float height, const float depth)
{
    std::vector<GLfloat> points;

    const auto radiusX = width / 2;
    const auto radiusY = height / 2;
    const auto radiusZ = depth / 2;

    //point 1
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ - radiusZ);
    //point 2
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ - radiusZ);
    //point 3
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ - radiusZ);
    //point 4
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ - radiusZ);
    //point 5
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ + radiusZ);
    //point 6
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ + radiusZ);
    //point 7
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ + radiusZ);
    //point 8
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ + radiusZ);

    return points;
}