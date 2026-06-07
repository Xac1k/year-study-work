//
// Created by xac1k on 6/6/26.
//

#include "./Task.h"

#include "../Utils.h"

Task JsonTaskParse(const crow::json::rvalue& source) {
    ValidPathOrThrow(source, "start");
    ValidPathOrThrow(source, "end");

    return std::make_pair(GetJsonPoint(source, "start"), GetJsonPoint(source, "end"));
}

Tasks TaskParser::Parse(const crow::json::rvalue &source) {
    if (!source.has("tasks") || source["tasks"].t() != crow::json::type::List)
        throw std::invalid_argument("tasks is not a list");

    Tasks tasks;
    for (auto taskJson : source["tasks"])
        tasks.push_back(JsonTaskParse(taskJson));

    return tasks;
}
