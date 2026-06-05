//
// Created by xac1k on 6/4/26.
//

#include "./JsonDependencyContainerParser.h"

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

EntityGenerator::Config GetEntityGeneratorConfig(const crow::json::rvalue& source) {
    if (!source.has("generator") || source["generator"].t() != crow::json::type::Object)
        throw std::invalid_argument("generator configuration is not a JSON object");
    auto gen = source["generator"];

    return {
        .limitationsX = GetRange(gen, "limitationsX"),
        .limitationsY = GetRange(gen, "limitationsY"),
        .limitationsZ = GetRange(gen, "limitationsZ"),
        .countWayPoints = GetSizeT(gen, "countWayPoints"),
        .maxGenerationIterations = GetSizeT(gen, "maxGenerationIterations")
    };
}

Updater::Config GetUpdaterConfig(const crow::json::rvalue& source) {
    if (!source.has("updater") || source["updater"].t() != crow::json::type::Object)
        throw std::invalid_argument("dependencyContainer::updater configuration is not a JSON object");

    auto updater = source["updater"];
    if (!updater.has("initialEnergy") || updater["initialEnergy"].t() != crow::json::type::Number)
        throw std::invalid_argument("dependencyContainer::updater::initialEnergy configuration is not a JSON number");
    if (!updater.has("maxIterations") || updater["maxIterations"].t() != crow::json::type::Number)
        throw std::invalid_argument("dependencyContainer::updater::maxIterations configuration is not a JSON number");

    return {
        .initialEnergy = updater["initialEnergy"].d(),
        .maxIterations = updater["maxIterations"].u(),
    };
}

Estimator::Config GetEstimatorConfig(const crow::json::rvalue &source) {
    if (!source.has("estimator") || source["estimator"].t() != crow::json::type::Object)
        throw std::invalid_argument("estimator configuration is not a JSON object");

    ValidPathOrThrow(source["estimator"], "coefficients:ThreatAvoidance", ':');
    ValidPathOrThrow(source["estimator"], "coefficients:PathMinimizing", ':');
    ValidPathOrThrow(source["estimator"], "coefficients:VarianceMinimizing", ':');
    ValidPathOrThrow(source["estimator"], "coefficients:SmoothMaximizing", ':');
    ValidPathOrThrow(source["estimator"], "coefficients:ThreatImportance", ':');

    auto coefficients = source["estimator"]["coefficients"];
    return {
        .limitations = {},
        .coefficients = {
            .ThreatAvoidance = GetDouble(coefficients, "ThreatAvoidance"),
            .PathMinimizing = GetDouble(coefficients, "PathMinimizing"),
            .VarianceMinimizing = GetDouble(coefficients, "VarianceMinimizing"),
            .SmoothMaximizing = GetDouble(coefficients, "SmoothMaximizing"),
            .ThreatImportance = GetDouble(coefficients, "ThreatImportance"),
    }};
}

std::shared_ptr<DependencyContainer> JsonDependencyContainerParser::Parse(const crow::json::rvalue source) {
    const Estimator::Config estimatorConfig = GetEstimatorConfig(source);
    const Updater::Config updaterConfig = GetUpdaterConfig(source);
    const EntityGenerator::Config generatorConfig = GetEntityGeneratorConfig(source);

    return NewDependencyContainer(estimatorConfig, updaterConfig, generatorConfig);
}
