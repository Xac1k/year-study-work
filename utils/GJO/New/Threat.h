//
// Created by xac1k on 5/24/26.
//

#ifndef MAIN_THREAT_H
#define MAIN_THREAT_H
#include "Cylinder.h"
#include "Shpere.h"

enum class ThreatType{Air_Defense, Radar};
class IThreat {
public:
    virtual ~IThreat() = default;
    virtual ThreatType GetType()=0;
};

class RadarThreat : public IThreat, public Sphere {
public:
    ThreatType GetType() override {
        return ThreatType::Radar;
    };
};

class AirDefenseThreat : public IThreat, public Cylinder {
public:
    ThreatType GetType() override {
        return ThreatType::Air_Defense;
    };
};

#endif //MAIN_THREAT_H