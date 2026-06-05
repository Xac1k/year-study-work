//
// Created by xac1k on 5/24/26.
//

#ifndef MAIN_СYLINDER_H
#define MAIN_СYLINDER_H
#include "Shpere.h"

class Cylinder : public Sphere {
public:
    Cylinder() = default;
    Cylinder(Point3d c, double r, double h);
    Cylinder& SetHeight(const double &h);
    [[nodiscard]] double GetHeight() const;
private:
    double m_height{};
};


#endif //MAIN_СYLINDER_H