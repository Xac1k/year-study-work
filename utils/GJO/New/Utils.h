//
// Created by xac1k on 5/27/26.
//

#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H
#include <tuple>

#include "Point.h"


class Utils {
public:
    static std::tuple<double, double> calculateYawPitchAngles(const Point3d &p_prev, const Point3d &p_curr, const Point3d &p_next);
};

#endif //MAIN_UTILS_H