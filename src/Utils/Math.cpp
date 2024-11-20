#include "Utils/Math.hpp"
#include <cmath>


f32 CalculateSfmlLocalAngle(const Vec2f& vec) {
    Vec2f coor_origin = Vec2f(0, -1);
    f32 angle = -std::acos((vec * coor_origin) / (vec.length() * coor_origin.length()));
    f32 cross = vec.x * coor_origin.y - vec.y * coor_origin.x;
    if (cross < 0) {
        angle = 2 * PI - angle;
    }
    angle *= (180.0 / PI);
    return angle;
}
