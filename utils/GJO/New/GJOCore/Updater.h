//
// Created by xac1k on 5/27/26.
//

#ifndef MAIN_UPDATER_H
#define MAIN_UPDATER_H
#include <optional>
#include <random>

#include "Estimator.h"
#include "LevyFlight.h"
#include "Types.h"


class Updater {
public:
    Updater() {
        std::random_device rd;
        m_generator = std::make_shared<std::mt19937>(rd());
    };
    void Update(Entities &entities, const SharedThreats& threats, const Estimator& estimator);

    struct Config {
        double initialEnergy;
        size_t maxIterations;
    };

    Updater& SetConfig(const Config&);
private:
    void UpdateTrajectories(const SharedEntities &entities);
    void UpdateEnergy(const SharedEntities &entities, size_t currentIterations);
    std::uniform_real_distribution<> GetEnergyGenerator();

    std::optional<Config> m_config;
    std::shared_ptr<std::mt19937> m_generator = nullptr;
    std::optional<std::uniform_real_distribution<>> m_energyGenerator = std::nullopt;
    LevyFlight m_levyGenerator;
};


#endif //MAIN_UPDATER_H