//
// Created by xac1k on 5/27/26.
//

#include "./LevyFlight.h"

std::uniform_real_distribution<> LevyFlight::GetNumberGenerator() {
    if (!m_numberGenerator.has_value())
        m_numberGenerator = std::uniform_real_distribution<>(0.0001, 0.9999);

    return m_numberGenerator.value();
}

void LevyFlight::CalculateSigma() {
    const double numerator = std::tgamma(1 + beta) * std::sin(M_PI * beta / 2.0);
    const double denominator = beta * std::pow(2.0, (beta - 1.0) / 2.0) * std::tgamma((1.0 + beta) / 2.0);
    sigma = std::pow(numerator / denominator, 1.0 / beta);
}

double LevyFlight::GetValue() {
    std::uniform_real_distribution<> numberGenerator = GetNumberGenerator();

    const double u = numberGenerator(*m_generator);
    const double v = numberGenerator(*m_generator);

    return 0.05 * (u * sigma) / std::pow(v, 1 / beta);
}

std::vector<double> LevyFlight::GetVector(const size_t size) {
    std::vector<double> vec;
    vec.reserve(size);
    for (size_t i = 0; i < size; i++)
        vec.push_back(GetValue());
    return vec;
}

std::vector<Point3d> LevyFlight::GetPoints(const size_t size) {
    std::vector<Point3d> points;
    points.reserve(size);
    for (size_t i = 0; i < size; i++) {
        Point3d p;
        p.x = GetValue();
        p.y = GetValue();
        p.z = GetValue();
        points.push_back(p);
    }
    return points;
}
