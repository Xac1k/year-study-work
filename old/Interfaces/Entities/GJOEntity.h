//
// Created by xac1k on 4/27/26.
//

#ifndef MAIN_GJOENTITY_H
#define MAIN_GJOENTITY_H
#include "../Core/Context.h"
#include <ranges>
#include <cmath>
#include <vector>
#include <iostream>

namespace IGJO {
    struct IFitnessContext : IContext {};
    struct IEnergyContext : IContext {};

    template<typename ContextT = IEnergyContext>
    class ITEnergy {
    public:
        virtual ~ITEnergy() = default;
        virtual double ComputeEnergy(const ContextT& ctx) const = 0;
    };

    template<typename ContextT = IFitnessContext>
    class ITFitness {
    public:
        virtual ~ITFitness() = default;
        virtual double Fitness(const ContextT& context) const = 0;
    protected:
        mutable std::optional<double> m_cacheFitness;
    };

    template<unsigned int N>
    class TEntityBase {
    public:
        TEntityBase() = default;
        explicit TEntityBase(std::array<double, N> values) noexcept {
            m_components = values;
        }
        TEntityBase(const TEntityBase& entity) noexcept {
            m_components = entity.m_components;
        }
        TEntityBase(TEntityBase&& entity) noexcept {
            m_components = std::move(entity.m_components);
        }
        TEntityBase& operator=(const TEntityBase& entity) noexcept = default;
        TEntityBase& operator=(TEntityBase&& entity) noexcept {
            m_components = std::move(entity.m_components);
            return *this;
        }
        explicit TEntityBase(std::vector<double> vect) {
            if (vect.size() != N)
                throw std::invalid_argument("The number of elements of the entities must be the same");
            m_components.reserve(N);
            for (unsigned int i = 0; i < N; ++i)
                m_components.emplace_back(vect[i]);
        }

        TEntityBase operator-(const TEntityBase& other) const noexcept {
            TEntityBase result;
            for (size_t i = 0; i < N; ++i) {
                result.m_components[i] = m_components[i] - other.m_components[i];
            }
            return result;
        }
        TEntityBase operator+(const TEntityBase& other) const noexcept {
            TEntityBase result;
            for (size_t i = 0; i < N; ++i) {
                result.m_components[i] = m_components[i] + other.m_components[i];
            }
            return result;
        }
        TEntityBase operator-(const double& multiplier) const noexcept {
            TEntityBase result;
            for (size_t i = 0; i < N; ++i) {
                result.m_components[i] = m_components[i] * multiplier;
            }
            return result;
        }
        TEntityBase operator/(const double& divisor) const {
            return *this * 1/divisor;
        }
        TEntityBase Abs() const noexcept {
            TEntityBase result;
            for (size_t i = 0; i < N; ++i) {
                result.m_components[i] = std::abs(m_components[i]);
            }
            return result;
        }
        TEntityBase operator*(const TEntityBase& other) const {
            TEntityBase result;
            for (size_t i = 0; i < N; ++i) {
                result.m_components[i] = m_components[i] * other.m_components[i];
            }
            return result;
        };
    protected:
        std::array<double, N> m_components = {};
    };

    template<unsigned int N, typename FitnessCtx = IFitnessContext, typename EnergyCtx = IEnergyContext>
    class ITEntity : public TEntityBase<N>, public ITFitness<FitnessCtx>, public ITEnergy<EnergyCtx> {};
}

#endif //MAIN_GJOENTITY_H