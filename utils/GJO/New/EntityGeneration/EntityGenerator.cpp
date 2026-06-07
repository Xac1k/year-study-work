//
// Created by xac1k on 5/24/26.
//

#include "./EntityGenerator.h"

#include <algorithm>
#include <stdexcept>

void NextChaoticTentView(double& value) {
    if (value < 0.0) value = 0.0;
    if (value > 1.0) value = 1.0;

    if (value <= 0.5) {
        value = value / 0.5;
    } else {
        value = (1.0 - value) / 0.5;
    }
}

void NextChaoticTentView(Point3d& point) {
    NextChaoticTentView(point.x);
    NextChaoticTentView(point.y);
    NextChaoticTentView(point.z);
}

Entity EntityGenerator::Generate(const Point3d& startPoint, const Point3d& endPoint) {
    if (!m_config.has_value())
        throw std::logic_error {"EntityGenerator: Firstly you need to set up config."};
    const auto config = m_config.value();

    std::uniform_real_distribution<> coordGenerator(0, 1);
    std::vector<Point3d> points;
    points.reserve(config.countWayPoints + 2);
    points.push_back(startPoint);

    for (size_t idx = 0; idx < config.countWayPoints; ++idx) {
        Point3d p {
            coordGenerator(*m_generator),
            coordGenerator(*m_generator),
            coordGenerator(*m_generator)
        };

        for (size_t id = 0; id < config.maxGenerationIterations; ++id)
            NextChaoticTentView(p);

        p.x = config.limitationsX.min + (config.limitationsX.max - config.limitationsX.min) * p.x;
        p.y = config.limitationsY.min + (config.limitationsY.max - config.limitationsY.min) * p.y;
        p.z = config.limitationsZ.min + (config.limitationsZ.max - config.limitationsZ.min) * p.z;

        points.push_back(p);
    }
    points.push_back(endPoint);

    return Entity{points};
}

EntityGenerator &EntityGenerator::SetConfig(const Config &c) {
    m_config = std::make_optional(c);
    return *this;
}




