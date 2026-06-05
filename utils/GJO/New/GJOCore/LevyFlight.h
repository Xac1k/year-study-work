//
// Created by xac1k on 5/27/26.
//

#ifndef MAIN_LEVYFLIGHT_H
#define MAIN_LEVYFLIGHT_H
#include <memory>
#include <optional>
#include <random>

#include "../Point.h"

class LevyFlight {
public:
    LevyFlight() {
        std::random_device rd;
        m_generator = std::make_shared<std::mt19937>(rd());
        CalculateSigma();
    };
    double GetValue();

    std::vector<double> GetVector(size_t size);
    std::vector<Point3d> GetPoints(size_t size);
private:
    void CalculateSigma();
    std::uniform_real_distribution<> GetNumberGenerator();

    double sigma = 0;
    double beta = 1.5;

    std::shared_ptr<std::mt19937> m_generator = nullptr;
    std::optional<std::uniform_real_distribution<>> m_numberGenerator = std::nullopt;
};


#endif //MAIN_LEVYFLIGHT_H