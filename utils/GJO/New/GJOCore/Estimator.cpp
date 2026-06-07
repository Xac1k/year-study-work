//
// Created by xac1k on 5/24/26.
//

#include "./Estimator.h"

#include <cmath>
#include <iostream>
#include <ostream>

double CalculateTotalLength(Entity& entity) {
    double totalLength = 0.0;
    for (size_t idx = 0; idx < entity.GetSize() - 1; idx++) {
        auto [x, y, z] = entity[idx + 1] - entity[idx];
        totalLength += std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
    }
    return totalLength;
}

double CalculateHeightVariance(const Entity& entity) {
    double sumOfHeight = 0.0;
    for (const auto p: entity.GetPoints())
        sumOfHeight += p.z;

    double SquaredHeightDiff = 0;
    for (const auto p: entity.GetPoints())
        SquaredHeightDiff += std::pow(p.z - sumOfHeight / entity.GetSize(), 2);

    return SquaredHeightDiff / entity.GetSize();
}

double CalculateVectorLength(const Point3d &v) {
    return std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2) + std::pow(v.z, 2));
}

// Угол в радианах.
double GetAngleBetweenVectors(const Point3d &v1, const Point3d &v2) {
    const auto scalar = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    const auto v1len = CalculateVectorLength(v1);
    const auto v2len = CalculateVectorLength(v2);

    const auto cos = scalar / (v1len * v2len);
    return std::acos(cos);
}

double CalculateSmooth(Entity& entity) {
    double sumOfSmooth = 0.0;
    for (size_t idx = 0; idx < entity.GetSize() - 3; idx++) {
        const auto v1 = entity[idx + 1] - entity[idx];
        const auto v2 = entity[idx + 2] - entity[idx + 1];
        const auto v3 = entity[idx + 3] - entity[idx + 2];

        sumOfSmooth += GetAngleBetweenVectors(v3, v2) - GetAngleBetweenVectors(v2, v1);
    }

    return sumOfSmooth;
}

Point3d GetCenter(const std::shared_ptr<IThreat>& t) {
    if (t->GetType()  == ThreatType::Air_Defense) {
        return std::dynamic_pointer_cast<AirDefenseThreat>(t)->GetCenter();
    }
    if (t->GetType() == ThreatType::Radar) {
        return std::dynamic_pointer_cast<RadarThreat>(t)->GetCenter();
    }

    throw std::runtime_error("GetCenter: Unknown threat type");
}

Point3d FindNearestPointOnTrajectoryToDangerousCenter(Entity& e, const std::shared_ptr<IThreat>& t) {
    Point3d nearestPoint;
    double minLength = std::numeric_limits<double>::max();

    auto [x1, y1, z1] = GetCenter(t);
    for (size_t idx = 0; idx < e.GetSize() - 1; idx++) {
        auto [x2, y2, z2] = e[idx];
        auto [x3, y3, z3] = e[idx + 1];

        const auto numerator = (x3 - x2) * x1 - (y3 - y2) * y1 - (z3 - z2) * z1;
        const auto denominator = std::pow(x3 - x2, 2) + std::pow(y3 - y2, 2) + std::pow(z3 - z2, 2);
        const auto minT = numerator / denominator;

        Point3d minPoint ={
            .x =  (x3 - x2) * minT + x2,
            .y =  (y3 - y2) * minT + y2,
            .z =  (z3 - z2) * minT + z2
        };

        auto lengthToCenterThreat = CalculateVectorLength(GetCenter(t) - minPoint);
        if (minLength < lengthToCenterThreat) {
            minLength = lengthToCenterThreat;
            nearestPoint = minPoint;
        }
    }

    return nearestPoint;
};

bool IsMinPointIntoThreatArea(const Point3d& p, const std::shared_ptr<IThreat>& t) {
    if (t->GetType()  == ThreatType::Air_Defense) {
        auto airDefenseThreat = std::static_pointer_cast<AirDefenseThreat>(t);

        auto distanceBetweenCenterOfCircleAndMinPoint2d = CalculateVectorLength(
            Point3d(p.x - airDefenseThreat->GetCenter().x, p.y - airDefenseThreat->GetCenter().y, 0)
        );

        if (airDefenseThreat->GetRadius() < distanceBetweenCenterOfCircleAndMinPoint2d)
            return false;

        const auto minZ = airDefenseThreat->GetCenter().z;
        const auto maxZ = airDefenseThreat->GetCenter().z + airDefenseThreat->GetHeight();

        return minZ < p.z && p.z < maxZ;
    }
    if (t->GetType()  == ThreatType::Radar) {
        const auto radarThreat = std::static_pointer_cast<AirDefenseThreat>(t);
        const auto distanceBetweenCenterAndMinPoint = CalculateVectorLength(radarThreat->GetCenter() - p);
        return distanceBetweenCenterAndMinPoint < radarThreat->GetRadius();
    }
    throw std::runtime_error("IsMinPointIntoThreatArea: Unknown threat type");
}

double CalculateDangerousToThreat(double distance, const std::shared_ptr<AirDefenseThreat>& t, const double importance) {
    return std::pow(importance, 2) / std::pow(distance, 4);
}

double CalculateDangerousToThreat(double distance, const std::shared_ptr<RadarThreat>& t, const double importance) {
    return std::pow(importance, 2) / distance;
}

double CalculateDangerous(Entity& e, const SharedThreats& threats, const double avoidance) {
    double sumOfDangerous = 0.0;
    for (const auto& threat: threats) {
        auto nearestPoint = FindNearestPointOnTrajectoryToDangerousCenter(e, threat);
        if (!IsMinPointIntoThreatArea(nearestPoint, threat)) continue;

        if (threat->GetType()  == ThreatType::Radar) {
            auto t = std::static_pointer_cast<RadarThreat>(threat);
            sumOfDangerous += CalculateDangerousToThreat(CalculateVectorLength(nearestPoint - t->GetCenter()), t, avoidance);
        }
        if (threat->GetType()  == ThreatType::Air_Defense) {
            auto t = std::static_pointer_cast<AirDefenseThreat>(threat);
            sumOfDangerous += CalculateDangerousToThreat(CalculateVectorLength(nearestPoint - t->GetCenter()), t, avoidance);
        }
    }
    return sumOfDangerous;
};

void Estimator::Estimate(const SharedEntities &entities, const SharedThreats &threats) const {
    for (auto& entity : entities) {
        const auto totalLength = CalculateTotalLength(*entity);
        const auto heightVariance = CalculateHeightVariance(*entity);
        const auto smooth = CalculateSmooth(*entity);
        const auto dangerous = CalculateDangerous(*entity, threats, m_config.coefficients.ThreatAvoidance);

        double totalCost = 0;
        totalCost += m_config.coefficients.PathMinimizing * totalLength;
        totalCost += m_config.coefficients.VarianceMinimizing * heightVariance;
        totalCost += m_config.coefficients.SmoothMaximizing * smooth;
        totalCost += m_config.coefficients.ThreatImportance * dangerous;

        entity->SetEstimation(totalCost);
    }
}

Estimator &Estimator::SetConfig(const Config &c) {
    double resultingCoefficient = c.coefficients.PathMinimizing;
    resultingCoefficient += c.coefficients.VarianceMinimizing;
    resultingCoefficient += c.coefficients.SmoothMaximizing;
    resultingCoefficient += c.coefficients.ThreatImportance;

    if (resultingCoefficient > 1)
        throw std::runtime_error("The coefficients of estimator need equals not more than 1.");

    m_config = c;
    return *this;
}



