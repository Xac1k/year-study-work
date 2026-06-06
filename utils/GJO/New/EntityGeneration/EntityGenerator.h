//
// Created by xac1k on 5/24/26.
//

#ifndef MAIN_ENTITYGENERATOR_H
#define MAIN_ENTITYGENERATOR_H
#include <memory>
#include <optional>
#include <random>

#include "IEntityGenerator.h"
#include "../GJOCore/Entity.h"

struct Range { double min, max; };

class EntityGenerator : public IEntityGenerator {
public:
    EntityGenerator() {
        std::random_device rd;
        std::mt19937 generator(rd());

        m_generator = std::make_shared<std::mt19937>(generator);
    };
    struct Config {
        Range limitationsX;
        Range limitationsY;
        Range limitationsZ;

        size_t countWayPoints;
        size_t maxGenerationIterations;
    };

    Entity Generate(const Point3d& startPoint, const Point3d& endPoint) override;
    EntityGenerator& SetConfig(const Config& c);
private:
    std::optional<Config> m_config = std::nullopt;
    std::shared_ptr<std::mt19937> m_generator;
};

#endif //MAIN_ENTITYGENERATOR_H