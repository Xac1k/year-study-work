//
// Created by xac1k on 5/24/26.
//

#include "./Point.h"

#include <cmath>

Point3d Point3d::abs() const {
    Point3d result = *this;
    result.x = std::abs(x);
    result.y = std::abs(y);
    result.z = std::abs(z);
    return result;
}

Point3d Point3d::operator*(const Point3d &value) const {
    Point3d result = *this;
    result.x *= value.x;
    result.y *= value.y;
    result.z *= value.z;
    return result;
}

Point3d Point3d::operator*(const double multiplier) const {
    Point3d result = *this;
    result.x *= multiplier;
    result.y *= multiplier;
    result.z *= multiplier;
    return result;
}

Point3d Point3d::operator+(const Point3d &value) const {
    Point3d result = *this;
    result.x += value.x;
    result.y += value.y;
    result.z += value.z;
    return result;
}

Point3d Point3d::operator-(const Point3d &value) const {
    Point3d result = *this;
    result.x -= value.x;
    result.y -= value.y;
    result.z -= value.z;
    return result;
}
