//
// Created by xac1k on 5/27/26.
//

#ifndef MAIN_VECTOR_H
#define MAIN_VECTOR_H

struct Vector2d {
    double x, y;
    [[nodiscard]] double Length() const;
    [[nodiscard]] double Dot(Vector2d other) const;
    [[nodiscard]] double Cross(const Vector2d &other) const;
};

struct Vector3d {
    double x, y, z;
    [[nodiscard]] double Length() const;
    [[nodiscard]] double Dot(const Vector3d &other) const;
};

#endif //MAIN_VECTOR_H