//
// Created by xac1k on 5/24/26.
//

#ifndef MAIN_SHPERE_H
#define MAIN_SHPERE_H
#include "Point.h"


class Sphere {
public:
    Sphere()=default;
    Sphere(Point3d c, double r): m_center(c), m_radius(r) {};

    [[nodiscard]] Point3d GetCenter() const ;
    Sphere& SetCenter(const Point3d& c);

    [[nodiscard]] double GetRadius() const;
    Sphere& SetRadius(const double& r);
private:
    Point3d m_center;
    double m_radius{};
};


#endif //MAIN_SHPERE_H