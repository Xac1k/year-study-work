//
// Created by xac1k on 5/24/26.
//

#ifndef MAIN_POINT_H
#define MAIN_POINT_H

struct Point3d {
    double
    x=0,
    y=0,
    z=0;

    Point3d operator*(const Point3d& value) const;
    [[nodiscard]] Point3d abs() const;
    Point3d operator*(double multiplier) const;

    Point3d operator+(const Point3d& value) const;
    Point3d operator-(const Point3d& value) const;
};

#endif //MAIN_POINT_H