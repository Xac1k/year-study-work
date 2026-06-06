//
// Created by xac1k on 5/24/26.
//

#include "Shpere.h"

Point3d Sphere::GetCenter() const {
    return m_center;
}


double Sphere::GetRadius() const {
    return m_radius;
}

Sphere& Sphere::SetCenter(const Point3d& c) {
    m_center = c;
    return *this;
}

Sphere& Sphere::SetRadius(const double& r) {
    m_radius = r;
    return *this;
}
