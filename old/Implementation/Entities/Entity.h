//
// Created by xac1k on 4/28/26.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include "../Core/Context.h"

namespace GJO::Drone{
    class Entity : IGJO::ITEntity<COUNT_OF_WAY_POINTS, FitnessCtx, EnergyCtx> {
        double ComputeEnergy(const EnergyCtx &ctx) const override;
        double Fitness(const  FitnessCtx&context) const override;
    };
}

#endif //MAIN_ENTITY_H