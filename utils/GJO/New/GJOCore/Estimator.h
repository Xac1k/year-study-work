//
// Created by xac1k on 5/24/26.
//

#ifndef MAIN_ESTIMATOR_H
#define MAIN_ESTIMATOR_H
#include "Types.h"

class Estimator {
public:
    //Устанавливает оценку каждой особи
    void Estimate(const SharedEntities&, const SharedThreats&) const;

    struct ImportanceCoefficients {
        double ThreatAvoidance;
        double PathMinimizing;
        double VarianceMinimizing;
        double SmoothMaximizing;
        double ThreatImportance;
    };
    struct Limitations {};

    struct Config {
        Limitations limitations;
        ImportanceCoefficients coefficients;
    };

    Estimator& SetConfig(const Config&);
private:
    Config m_config = {};
};


#endif //MAIN_ESTIMATOR_H