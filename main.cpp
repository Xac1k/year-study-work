//
// Created by xac1k on 4/27/26.
//

#include "./main.h"
#include "crow.h"
#include "curl/curl.h"
#include <filesystem>

#include "utils/GJO/New/DependencyContainer.h"
#include "utils/GJO/New/EntityGeneration/EntityFactory.h"
#include "utils/Server/DependencyContainer/JsonDependencyContainerParser.h"
#include "utils/Server/Task/Task.h"
#include "utils/Server/Threat/JsonThreatParser.h"

Entities SolveTasks(SharedThreats& threats,  std::shared_ptr<DependencyContainer>& container, const Tasks& tasks) {
    Entities population;
    for (auto [fst, snd] : tasks) {
        auto batch = container->entityFactory->NewEntities(container->batchSize, fst, snd);
        std::ranges::copy(batch, std::back_inserter(population));
    }

    container->entityUpdater->Update(population, threats, *container->entityEstimator);

    return population;
}

int main(int argc, char *argv[]) {
    crow::SimpleApp app;
    std::filesystem::path frontend_path = std::filesystem::current_path() / ".." / "frontend" / "index.html";

    CROW_ROUTE(app, "/api/v1/compute").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        const auto jsonBody = crow::json::load(req.body);

        if (!jsonBody) return crow::response(400, "Invalid JSON");
        if (!jsonBody.has("dependencyContainer")) return crow::response(400, "config is missing in body of request");
        if (!jsonBody.has("threats")) return crow::response(400, "threats is missing in body of request");
        if (jsonBody["threats"].t() != crow::json::type::List) return crow::response(400, "threats must be a list");
        if (jsonBody["dependencyContainer"].t() != crow::json::type::Object) return crow::response(400, "dependencyContainer must be an object");

        try {
            JsonThreatParser threatParser;
            JsonDependencyContainerParser containerParser;
            TaskParser taskParser;

            auto threats = threatParser.Parse(jsonBody["threats"]);
            auto container = containerParser.Parse(jsonBody["dependencyContainer"]);
            auto tasks = taskParser.Parse(jsonBody);

            auto minimizedPaths = SolveTasks(threats, container, tasks);
        }
        catch (std::exception& e) {
            return crow::response(400, e.what());
        }

        return crow::response(500, "Caught but,  Not Implemented.");
    });

    CROW_ROUTE(app, "/")
    ([](const crow::request& req, crow::response& res) {
        res.redirect("http://localhost:5173/");
        res.end();
    });

    app.port(8081).multithreaded().run();
}