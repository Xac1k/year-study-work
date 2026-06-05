//
// Created by xac1k on 6/3/26.
//

#ifndef YEAR_STUDY_WORK_JSONTHREATPARSER_H
#define YEAR_STUDY_WORK_JSONTHREATPARSER_H
#include <crow/json.h>
#include <string>
using namespace std::literals::string_literals;

#include "IThreatParser.h"

class JsonThreatParser : public IThreatParser<crow::json::rvalue> {
public:
    SharedThreats Parse(const crow::json::rvalue &source) override;
};

constexpr std::string Radar = "radar";
constexpr std::string AirDefense = "airdefense";

#endif //YEAR_STUDY_WORK_JSONTHREATPARSER_H