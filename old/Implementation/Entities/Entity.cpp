//
// Created by xac1k on 5/5/26.
//

#include "./Entity.h"

double GJO::Drone::Entity::ComputeEnergy(const EnergyCtx &ctx) const {
    const auto E1 = ctx.initialEnergy * (1 - ctx.iteration / ctx.maxIteration);
    const auto E0 = 2 * (static_cast<double>(std::rand()) / RAND_MAX) - 1;

    return E1 * E0;
}

double GJO::Drone::Entity::Fitness(const FitnessCtx &context) const {
    //TODO: implement
    return 0;
}

