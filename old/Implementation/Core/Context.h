//
// Created by xac1k on 4/28/26.
//

#ifndef MAIN_CONTEXT_IMPL_H
#define MAIN_CONTEXT_IMPL_H

#include "../../../../main.h"
#include "../../Interfaces/Entities/GJOEntity.h"
#include "../../Interfaces/Entities/GJOEntityGenerator.h"

namespace GJO::Drone {
    class IThreat;

    struct ImportanceInError {
        double lengthCoef = 0;
        double heightStdDevCoef = 0;
        double smoothCoef = 0;
        double threatCoef = 0;
        double errorCoef = 0;
        double cooperativeCoef = 0;
    };

    struct FitnessCtx : IGJO::IFitnessContext {
        bool cooperativePlanning = false;

        std::vector<std::shared_ptr<IGJO::TEntityBase<COUNT_OF_WAY_POINTS>>> trajectories;
        std::vector<std::shared_ptr<IThreat>> threats;

        ImportanceInError coefficients;
    };

    struct EnergyCtx : IGJO::IEnergyContext {
        unsigned int iteration = 0;
        unsigned int maxIteration = 0;
        double initialEnergy = 0;
    };

    struct LimitationsCtx : IGJO::ILimitationsContext {
        double minHeight = 0.0;
        double maxHeight = 0.0;

        double minWidth = 0.0;
        double maxWidth = 0.0;

        //TODO: Параметры жестких ограничений, чтобы генерировать только валидное состояние
    };
}

#endif //MAIN_CONTEXT_H
