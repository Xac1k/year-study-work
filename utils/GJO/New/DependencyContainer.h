//
// Created by xac1k on 6/1/26.
//

#ifndef MAIN_DEPENDENCYCONTAINER_H
#define MAIN_DEPENDENCYCONTAINER_H
#include <memory>

#include "EntityGeneration/EntityGenerator.h"
#include "GJOCore/Estimator.h"
#include "GJOCore/Updater.h"

class EntityFactory;

struct DependencyContainer {
    std::shared_ptr<EntityFactory> entityFactory;
    std::shared_ptr<Estimator> entityEstimator;
    std::shared_ptr<Updater> entityUpdater;
};

std::shared_ptr<DependencyContainer> NewDependencyContainer(Estimator::Config estimatorConfig, Updater::Config updaterConfig, EntityGenerator::Config genConfig);

#endif //MAIN_DEPENDENCYCONTAINER_H