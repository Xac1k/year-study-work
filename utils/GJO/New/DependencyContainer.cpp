//
// Created by xac1k on 6/1/26.
//

#include "./DependencyContainer.h"

#include "EntityGeneration/EntityGenerator.h"
#include "EntityGeneration/EntityFactory.h"

std::shared_ptr<DependencyContainer> NewDependencyContainer(Estimator::Config estimatorConfig, Updater::Config updaterConfig, EntityGenerator::Config genConfig, size_t batchSize) {
    auto container = std::make_shared<DependencyContainer>(DependencyContainer{});

    EntityFactory entityFactory;
    EntityGenerator entityGenerator;
    Estimator entityEstimator;
    Updater entityUpdater;

    entityGenerator.SetConfig(genConfig);
    entityEstimator.SetConfig(estimatorConfig);
    entityUpdater.SetConfig(updaterConfig);

    const auto generator = std::static_pointer_cast<IEntityGenerator>(std::make_shared<EntityGenerator>(entityGenerator));
    entityFactory.SetStrategy(generator);

    container->entityEstimator = std::make_shared<Estimator>(entityEstimator);
    container->entityFactory = std::make_shared<EntityFactory>(entityFactory);
    container->entityUpdater = std::make_shared<Updater>(entityUpdater);
    container->batchSize = batchSize;

    return container;
}

// {
//     .limitationsX = {10, 10},
//     .limitationsY = {10, 10},
//     .limitationsZ = {10, 10},
//     .countWayPoints = 1,
//     .maxGenerationIterations = 5
// });
// {
// .limitations = {
//
// },
// .coefficients = {
//     .ThreatAvoidance = 1,
//     .PathMinimizing = 0.25,
//     .VarianceMinimizing = 0.25,
//     .SmoothMaximizing = 0.25,
//     .ThreatImportance = 0.25
// }});


// {
//     .initialEnergy = 1,
//     .maxIterations = 1000
// });