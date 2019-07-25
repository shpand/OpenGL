#include "Square.h"
#include <GL/glew.h>


Square::Square(const float centerX, const float centerY, const float width, const float height)
{
    _points = CalculatePointsWithColor(centerX, centerY, width, height);
}


Square::~Square()
{
}

std::vector<GLfloat> Square::GetPoints()
{
    return _points;
}

std::vector<unsigned> Square::GetIndicies()
{
    return _indicies;
}

std::vector<GLfloat> Square::CalculatePoints(const float centerX, const float centerY, const float width, const float height)
{
    std::vector<GLfloat> points;

    const auto radiusX = width / 2;
    const auto radiusY = height / 2;

    //point 1
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    //point 2
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    //point 3
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    //point 4
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);

    return points;
}

std::vector<GLfloat> Square::CalculatePointsWithUV(const float centerX, const float centerY, const float width, const float height)
{
    std::vector<GLfloat> points;

    const auto radiusX = width / 2;
    const auto radiusY = height / 2;

    //point 1
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    //uv
    points.push_back(0);
    points.push_back(1);
    //point 2
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    //uv
    points.push_back(0);
    points.push_back(0);
    //point 3
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    //uv
    points.push_back(1);
    points.push_back(0);
    //point 4
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    //uv
    points.push_back(1);
    points.push_back(1);

    return points;
}

std::vector<GLfloat> Square::CalculatePointsWithColor(const float centerX, const float centerY, const float width, const float height)
{
    std::vector<GLfloat> points;

    const auto radiusX = width / 2;
    const auto radiusY = height / 2;

    //point 1
    points.push_back(centerX - radiusX);
    points.push_back(centerY + radiusY);
    //color
    points.push_back(0);
    points.push_back(0);
    points.push_back(0);
    //point 2
    points.push_back(centerX - radiusX);
    points.push_back(centerY - radiusY);
    //color
    points.push_back(0);
    points.push_back(0);
    points.push_back(1);
    //point 3
    points.push_back(centerX + radiusX);
    points.push_back(centerY - radiusY);
    //color
    points.push_back(1);
    points.push_back(0);
    points.push_back(0);
    //point 4
    points.push_back(centerX + radiusX);
    points.push_back(centerY + radiusY);
    //color
    points.push_back(1);
    points.push_back(1);
    points.push_back(1);

    return points;
}
