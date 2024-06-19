#pragma once

#include <cmath>

// M_PI 상수 정의
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Transform
{
    struct Vertex
    {
        float x;
        float y;
    };

    struct Vector
    {
        float x_meter;
        float y_meter;
    };

    Vertex MoveVertex(Vertex point, Vector meter);
    Vertex RotateVertex(Vertex point, float angle_degree);
    Vertex ScaleVertex(Vertex point, Vector scale);
}
