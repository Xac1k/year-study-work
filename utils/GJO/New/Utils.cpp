//
// Created by xac1k on 5/27/26.
//

#include "Utils.h"

#include <algorithm>
#include <cmath>

#include "Vector.h"

std::tuple<double, double> Utils::calculateYawPitchAngles(const Point3d &p_prev, const Point3d &p_curr, const Point3d &p_next) {
    const Vector2d currSegment2d = { p_curr.x - p_prev.x, p_curr.y - p_prev.y };
    const Vector2d nextSegment2d = { p_next.x - p_curr.x, p_next.y - p_curr.y };
    const Vector3d currSegment3d = {p_next.x - p_curr.x, p_next.y - p_curr.y, p_next.z - p_curr.z};

    double cosYaw = currSegment2d.Dot(nextSegment2d) / (currSegment2d.Length() * nextSegment2d.Length());
    cosYaw = std::clamp(cosYaw, -1.0, 1.0);
    double yaw = std::acos(cosYaw);

    double cosPitch = currSegment2d.Length() / currSegment3d.Length();
    cosPitch = std::clamp(cosPitch, -1.0, 1.0);
    double pitch = std::acos(cosPitch);
    if (p_next.z < p_curr.z) pitch = -pitch;

    return std::make_tuple(yaw, pitch);
}
