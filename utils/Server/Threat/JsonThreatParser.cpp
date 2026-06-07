//
// Created by xac1k on 6/3/26.
//

#include "./JsonThreatParser.h"

#include "../Utils.h"

ThreatType GetJsonTypeOfThreat(const crow::json::rvalue& candidate) {
    if (!candidate.has("type") || candidate["type"].t() != crow::json::type::String)
        throw std::runtime_error("Type is not a string.");

    if (candidate["type"].s() == Radar)
        return ThreatType::Radar;

    if (candidate["type"].s() == AirDefense)
        return ThreatType::Air_Defense;

    throw std::runtime_error("Type is wrong. Valid types is: "+ Radar + " or " + AirDefense);
}

double GetJsonRadius(const crow::json::rvalue& candidate) {
    if (!candidate.has("radius"))
        throw std::runtime_error("No radius in json object.");
    if (candidate["radius"].t() != crow::json::type::Number)
        throw std::runtime_error("Radius isn't a number.");

    return candidate["radius"].d();
}

double GetJsonHeight(const crow::json::rvalue& candidate) {
    ThreatType type = GetJsonTypeOfThreat(candidate);
    if (type == ThreatType::Air_Defense) {
        if (!candidate.has("height") || candidate["height"].t() != crow::json::type::Number)
            throw std::runtime_error("No or not valid height in json object.");
        return candidate["height"].d();
    }

    return -1;
}

SharedThreat GetJsonThreat(const crow::json::rvalue& candidate) {
    const auto type = GetJsonTypeOfThreat(candidate);
    const auto radius = GetJsonRadius(candidate);
    const auto center = GetJsonPoint(candidate, "center");
    if (type == ThreatType::Air_Defense) {
        const auto height = GetJsonHeight(candidate);
        AirDefenseThreat threat;
        threat.SetHeight(height).SetCenter(center).SetRadius(radius);
        return std::static_pointer_cast<IThreat>(std::make_shared<AirDefenseThreat>(threat));
    }

    RadarThreat threat;
    threat.SetRadius(radius).SetCenter(center);
    return std::static_pointer_cast<IThreat>(std::make_shared<RadarThreat>(threat));
}

SharedThreats JsonThreatParser::Parse(const crow::json::rvalue &source) {
    if (source.t() != crow::json::type::List)
        throw std::runtime_error("The type of source data must be a list");

    SharedThreats threats;
    for (auto& item : source)
        threats.push_back(GetJsonThreat(item));

    return threats;
}