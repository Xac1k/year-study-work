//
// Created by xac1k on 5/27/26.
//

#include "./Updater.h"

Updater &Updater::SetConfig(const Config& config) {
    m_config = std::optional(config);
    return *this;
}

void Updater::Update(Entities &entities, const SharedThreats& threats, const Estimator& estimator) {
    std::vector<std::shared_ptr<Entity>> sharedEntities = {};
    for (auto& e : entities)
        sharedEntities.push_back(std::make_shared<Entity>(e));

    if (!m_config.has_value())
        throw std::runtime_error("Updater::Update: The config isn't set upped");

    const auto& config = m_config.value();
    for (size_t iter = 0; iter < config.maxIterations; iter++) {
        estimator.Estimate(sharedEntities, threats);
        UpdateEnergy(sharedEntities, iter);
        UpdateTrajectories(sharedEntities);
    }
}

void Updater::UpdateEnergy(const SharedEntities &entities, const size_t currentIterations) {
    auto& config = m_config.value();
    std::uniform_real_distribution<> energyGenerator = GetEnergyGenerator();

    for (auto& e : entities) {
        const double e0 = 2 * energyGenerator(*m_generator) - 1;
        const double e1 = config.initialEnergy * (1 - static_cast<double>(currentIterations) / static_cast<double>(config.maxIterations));
        e->SetEnergy(e1 * e0);
    }
}

std::uniform_real_distribution<> Updater::GetEnergyGenerator() {
    if (!m_energyGenerator.has_value())
        m_energyGenerator = std::uniform_real_distribution<>(0, 1);
    const auto& energyGenerator = m_energyGenerator.value();
    return energyGenerator;
}

std::tuple<SharedEntity, SharedEntity> FindMaleFemalePair(const SharedEntities &entities) {
    SharedEntity maleEntity = nullptr;
    SharedEntity femaleEntity = nullptr;

    for (auto& e : entities) {
        if (maleEntity == nullptr) {
            maleEntity = e;
            continue;
        }
        if (maleEntity->GetEstimation() >  e->GetEstimation()) {
            femaleEntity = maleEntity;
            maleEntity = e;
        }
    }

    return std::make_tuple(maleEntity, femaleEntity);
}

std::tuple<Entity, Entity> GetRlVectorsWithoutShiftingStartEnd(const SharedEntity &prey, LevyFlight& levyGenerator) {
    auto rl1 = Entity(levyGenerator.GetPoints(prey->GetSize()));
    auto rl2 = Entity(levyGenerator.GetPoints(prey->GetSize()));
    rl1[0] = {0, 0, 0};
    rl2[0] = {0, 0, 0};
    rl1[prey->GetSize() - 1] = {0, 0, 0};
    rl2[prey->GetSize() - 1] = {0, 0, 0};

    return std::make_tuple(rl1, rl2);
}

void Updater::UpdateTrajectories(const SharedEntities &entities) {
    const auto [male, female] = FindMaleFemalePair(entities);
    for (auto& prey : entities) {
        auto [rl1, rl2] = GetRlVectorsWithoutShiftingStartEnd(prey, m_levyGenerator);
        Entity y1, y2;

        if (std::abs(prey->GetEnergy()) < 1) {
            y1 = *male -  prey->GetEnergy() * (rl1 * *male - *prey).Abs();
            y2 = *female -  prey->GetEnergy() * (rl2 * *female - *prey).Abs();
        }
        else {
            y1 = *male -  prey->GetEnergy() * (*male - rl1 * *prey).Abs();
            y2 = *female -  prey->GetEnergy() * (*female - rl2 * *prey).Abs();
        }

        *prey.get() = (y1 + y2) / 2;
    }
}

