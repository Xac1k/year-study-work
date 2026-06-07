//
// Created by xac1k on 6/6/26.
//

#include "Utils.h"

Point3d GetJsonPoint(const crow::json::rvalue& candidate, const std::string &sourceName) {
    if (!candidate.has(sourceName))
        throw std::runtime_error("No " + sourceName + " in json object.");

    const auto& pointCandidate = candidate[sourceName];

    if (!pointCandidate.has("x") || !pointCandidate.has("y") || !pointCandidate.has("z"))
        throw std::runtime_error("Not a valid json object. Missing `x`, `y` or `z`");

    if (pointCandidate["x"].t() != crow::json::type::Number)
        throw std::runtime_error("Not a valid json object. X isn't a number.");
    if (pointCandidate["y"].t() != crow::json::type::Number)
        throw std::runtime_error("Not a valid json object. Y isn't a number.");
    if (pointCandidate["z"].t() != crow::json::type::Number)
        throw std::runtime_error("Not a valid json object. Z isn't a number.");

    return {pointCandidate["x"].d(), pointCandidate["y"].d(), pointCandidate["z"].d()};
}

void ValidPathOrThrow(const crow::json::rvalue& source, const std::string& path, const char& delimiter) {
    std::istringstream streamPath(path);

    std::string breadCrumbs;
    std::vector<std::string> pathComponents;
    while (std::getline(streamPath, breadCrumbs, delimiter))
        pathComponents.push_back(breadCrumbs);

    if (pathComponents.empty())
        throw std::invalid_argument("path are not valid");


    const crow::json::rvalue* checkable = &source;
    for (auto& crumb: pathComponents) {
        if (!checkable->has(crumb))
            throw std::invalid_argument("source doesn't have a path: " + path);

        checkable = &((*checkable)[crumb]);
    }
}

void ValidPathOrThrow(const crow::json::rvalue& source, const std::string& path) {
    if (!source.has(path))
        throw std::invalid_argument("source doesn't have a path: " + path);
}

Range GetRange(const crow::json::rvalue& source, const std::string& sourceName) {
    if (!source.has(sourceName) || source[sourceName].t() != crow::json::type::Object) {
        throw std::invalid_argument("config::" + sourceName + " is missing or not a object");
    }
    const auto& range = source[sourceName];
    if (!range.has("min") || range["min"].t() != crow::json::type::Number) {
        throw std::invalid_argument("config::min is missing or not a number");
    }
    if (!range.has("max") || range["max"].t() != crow::json::type::Number) {
        throw std::invalid_argument("config::max is missing or not a number");
    }

    return Range{
        .min = range["min"].d(),
        .max = range["max"].d()
    };
}

size_t GetSizeT(const crow::json::rvalue& source, const std::string& sourceName) {
    if (!source.has(sourceName) || source[sourceName].t() != crow::json::type::Number) {
        throw std::invalid_argument("config::" + sourceName + " is missing or not a number");
    }

    return source[sourceName].u();
}

double GetDouble(const crow::json::rvalue& source, const std::string& sourceName) {
    if (!source.has(sourceName) || source[sourceName].t() != crow::json::type::Number) {
        throw std::invalid_argument("config::" + sourceName + " is missing or not a number");
    }

    return source[sourceName].d();
}