//
// Created by xac1k on 5/27/26.
//

#include <cmath>

#include "Vector.h"

double Vector2d::Length() const {
    return std::sqrt(x * x + y * y);
}

double Vector2d::Dot(const Vector2d other) const {
    return x * other.x + y * other.y;
}

double Vector2d::Cross(const Vector2d &other) const {
    return x * other.y - y * other.x;
}

double Vector3d::Length() const {
    return std::sqrt(x * x + y * y + z * z);
}

double Vector3d::Dot(const Vector3d &other) const {
    return x * other.x + y * other.y + z * other.z;
}