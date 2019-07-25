#include "Cube.h"
#include <GL/glew.h>


Cube::Cube(const float centerX, const float centerY, const float centerZ, const float width, const float height, const float depth)
{
    _points = CalculatePointsWithUV(centerX, centerY, centerZ, width, height, depth);
}


Cube::~Cube()
{
}

std::vector<GLfloat> Cube::GetPoints()
{
    return _points;
}

std::vector<unsigned> Cube::GetIndicies()
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

std::vector<GLfloat> Cube::CalculatePointsWithUV(const float centerX, const float centerY, const float centerZ, const float width, const float height, const float depth)
{
    std::vector<GLfloat> points;

    const auto radiusX = width / 2;
    const auto radiusY = height / 2;
    const auto radiusZ = depth / 2;

    //point 1
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ - radiusZ);
    //uv
    points.push_back(0);
    points.push_back(1);
    //point 2
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ - radiusZ);
    //uv
    points.push_back(0);
    points.push_back(0.66f);
    //point 3
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ - radiusZ);
    //uv
    points.push_back(0.33f);
    points.push_back(0.66f);
    //point 4
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ - radiusZ);
    //uv
    points.push_back(0.33f);
    points.push_back(1);
    //point 5
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ + radiusZ);
    //uv
    points.push_back(0.66f);
    points.push_back(1);
    //point 6
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ + radiusZ);
    //uv
    points.push_back(0.66f);
    points.push_back(0.66f);
    //point 7
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ + radiusZ);
    //uv
    points.push_back(1);
    points.push_back(0.66f);
    //point 8
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ + radiusZ);
    //uv
    points.push_back(1);
    points.push_back(1);

    return points;
}

std::vector<GLfloat> Cube::CalculatePointsWithColors(const float centerX, const float centerY, const float centerZ, const float width, const float height, const float depth)
{
    std::vector<GLfloat> points;

    const auto radiusX = width / 2;
    const auto radiusY = height / 2;
    const auto radiusZ = depth / 2;

    //point 1
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ - radiusZ);
    //colors
    points.push_back(0);
    points.push_back(0);
    points.push_back(0);
    //point 2
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ - radiusZ);
    //colors
    points.push_back(0);
    points.push_back(0);
    points.push_back(1);
    //point 3
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ - radiusZ);
    //colors
    points.push_back(1);
    points.push_back(0);
    points.push_back(0);
    //point 4
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ - radiusZ);
    //colors
    points.push_back(0);
    points.push_back(1);
    points.push_back(0);
    //point 5
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ + radiusZ);
    //colors
    points.push_back(1);
    points.push_back(1);
    points.push_back(1);
    //point 6
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ + radiusZ);
    //colors
    points.push_back(0);
    points.push_back(1);
    points.push_back(1);
    //point 7
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    points.push_back(centerZ + radiusZ);
    //colors
    points.push_back(1);
    points.push_back(1);
    points.push_back(0);
    //point 8
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    points.push_back(centerZ + radiusZ);
    //colors
    points.push_back(1);
    points.push_back(0);
    points.push_back(1);

    return points;
}
