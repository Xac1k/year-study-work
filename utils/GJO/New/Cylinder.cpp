//
// Created by xac1k on 5/24/26.
//

#include "Cylinder.h"

double Cylinder::GetHeight() const {
    return m_height;
}

Cylinder::Cylinder(Point3d c, double r, double h): Sphere(c, r), m_height(h) {}

Cylinder& Cylinder::SetHeight(const double& h) {
    m_height = h;
    return *this;
}

