//
// Created by xac1k on 4/28/26.
//

#ifndef MAIN_ENTITYFACTORY_H
#define MAIN_ENTITYFACTORY_H
#include "../Entities/GJOEntityGenerator.h"

namespace detail {
    template<typename Entity>
    struct entity_traits;

    template<unsigned int N, typename FitnessCtx, typename EnergyCtx>
    struct entity_traits<IGJO::ITEntity<N, FitnessCtx, EnergyCtx>> {
        static constexpr unsigned int dimensions = N;
        using fitness_context = FitnessCtx;
        using energy_context = EnergyCtx;
    };
}

namespace IGJO {
    template<typename IEntityType, typename CtxGenLimitations = ILimitationsContext>
    class ITEntityFactory {
        using CtxFitness = detail::entity_traits<IEntityType>::fitness_context;
        using CtxEnergy = detail::entity_traits<IEntityType>::energy_context;
        static constexpr unsigned int N = detail::entity_traits<IEntityType>::dimensions;

        using GeneratorType = ITGenerationStrategy<N, CtxGenLimitations>;
    public:
        virtual ~ITEntityFactory() = default;
        ITEntityFactory() = default;

        void CreatePopulation(const unsigned int populationSize, const CtxGenLimitations& ctx) {
            if (!m_strategy) {
                throw std::runtime_error("Strategy not set!");
            }

            m_population.clear();
            m_population.reserve(populationSize);

            for (unsigned int i = 0; i < populationSize; ++i) {
                if (auto entity = m_strategy->Generate(ctx)) {
                    m_population.push_back(std::move(entity));
                }
            }
        }
        void SetStrategy(std::unique_ptr<GeneratorType> s) { //TODO: шаблонный параметр стратегии, т.к.
            m_strategy = std::move(s);
        }
        const std::vector<std::unique_ptr<IEntityType>>& GetPopulation() const {
            return m_population;
        }
        std::vector<std::unique_ptr<IEntityType>> GetPopulationCopy() const {
            std::vector<std::unique_ptr<IEntityType>> copy;
            copy.reserve(m_population.size());
            for (const auto& entity : m_population) {
                if (entity) {
                    copy.push_back(std::make_unique<IEntityType>(*entity.get()));
                }
            }
            return copy;
        }

        enum class SortOption {ASC, DESC};
        std::vector<std::unique_ptr<IEntityType>> SearchBest_n(unsigned int n, const CtxFitness& ctx, const SortOption order = SortOption::ASC) {
            if (m_population.empty()) return {};
            n = std::min(n, static_cast<unsigned int>(m_population.size()));

            std::vector<std::pair<double, size_t>> scored;
            scored.reserve(m_population.size());

            for (size_t i = 0; i < m_population.size(); ++i) {
                double fitness = m_population[i]->Fitness(ctx);
                scored.emplace_back(fitness, i);
            }

            std::sort(scored.begin(), scored.end(),
            [order](const auto& a, const auto& b) {
                return order == SortOption::DESC ? a.first > b.first : a.first < b.first;
            });

            std::vector<std::unique_ptr<IEntityType>> result;
            result.reserve(n);
            for (unsigned int i = 0; i < n && i < scored.size(); ++i) {
                size_t idx = scored[i].second;
                result.push_back(std::make_unique<IEntityType>(*m_population[idx]));
            }

            return result;
        }
        struct PopulationStats {
            double minFitness;
            double maxFitness;
            double avgFitness;
            double stdDev;
        };
        PopulationStats GetStatistics(const CtxFitness& ctx) const {
            PopulationStats stats{0.0, 0.0, 0.0, 0.0};
            if (m_population.empty()) return stats;

            std::vector<double> fitness;
            fitness.reserve(m_population.size());

            double sum = 0.0;
            auto maxF = static_cast<double>(-INFINITY);
            double minF = INFINITY;

            for (const auto& entity : m_population) {
                if (entity) {
                    double f = entity->Fitness(ctx);
                    fitness.push_back(f);
                    sum += f;
                    maxF = std::max(maxF, f);
                    minF = std::min(minF, f);
                }
            }

            const double mean = sum / static_cast<double>(fitness.size());
            double variance = 0.0;
            for (const double f : fitness) {
                variance += (f - mean) * (f - mean);
            }
            variance /= static_cast<double>(fitness.size());

            return {
                .minFitness = minF,
                .maxFitness = maxF,
                .avgFitness = mean,
                .stdDev = std::sqrt(variance),
            };
        }
        virtual void EvaluateAll(IFitnessContext& ctxFitness, IEnergyContext& ctxEnergy)=0; //TODO: Сделать фукнцию Evolve для эволюционирования популяции

        void Clear() {
            m_population.clear();
        }
        [[nodiscard]] size_t Size() const {
            return m_population.size();
        }
        [[nodiscard]] bool IsEmpty() const {
            return m_population.empty();
        }
    private:
        std::vector<std::unique_ptr<IEntityType>> m_population = {};
        std::unique_ptr<GeneratorType> m_strategy = nullptr;
    };
}

#endif //MAIN_ENTITYFACTORY_H