//
// Created by xac1k on 6/6/26.
//

#ifndef YEAR_STUDY_WORK_UTILS_H
#define YEAR_STUDY_WORK_UTILS_H

#include <crow.h>
#include "../GJO/New/EntityGeneration/EntityGenerator.h"

Point3d GetJsonPoint(const crow::json::rvalue& candidate, const std::string& sourceName);
void ValidPathOrThrow(const crow::json::rvalue& source, const std::string& path);
void ValidPathOrThrow(const crow::json::rvalue& source, const std::string& path, const char& delimiter);
Range GetRange(const crow::json::rvalue& source, const std::string& sourceName);
size_t GetSizeT(const crow::json::rvalue& source, const std::string& sourceName);
double GetDouble(const crow::json::rvalue& source, const std::string& sourceName);

#endif //YEAR_STUDY_WORK_UTILS_H