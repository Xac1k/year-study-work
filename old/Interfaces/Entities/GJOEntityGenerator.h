//
// Created by xac1k on 4/27/26.
//

#ifndef MAIN_GJOENTITYGENERATOR_H
#define MAIN_GJOENTITYGENERATOR_H
#include "GJOEntity.h"
#include "../Core/Context.h"
#include <memory>

namespace IGJO {
    struct ILimitationsContext : IContext {};

    template<unsigned int N, typename CtxGenLimitations = ILimitationsContext, typename CtxFitness = IFitnessContext, typename CtxEnergy = IEnergyContext>
    class ITGenerationStrategy {
        using EntityType = ITEntity<N, CtxFitness, CtxEnergy>;
    public:
        virtual ~ITGenerationStrategy() = default;
        virtual std::unique_ptr<EntityType> Generate(const CtxGenLimitations& ctx) = 0;
    };
}

#endif //MAIN_GJOENTITYGENERATOR_H