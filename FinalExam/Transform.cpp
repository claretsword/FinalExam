#include "Transform.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Transform
{
    Vertex MoveVertex(Vertex point, Vector meter)
    {
        point.x += meter.x_meter * 100.0f; // 1m = 100cm
        point.y += meter.y_meter * 100.0f; // 1m = 100cm
        return point;
    }

    Vertex RotateVertex(Vertex point, float angle_degree)
    {
        float angle_rad = angle_degree * M_PI / 180.0f;
        float cos_angle = cos(angle_rad);
        float sin_angle = sin(angle_rad);
        float new_x = point.x * cos_angle - point.y * sin_angle;
        float new_y = point.x * sin_angle + point.y * cos_angle;
        return { new_x, new_y };
    }

    Vertex ScaleVertex(Vertex point, Vector meter)
    {
        point.x *= meter.x_meter;
        point.y *= meter.y_meter;
        return point;
    }
}
