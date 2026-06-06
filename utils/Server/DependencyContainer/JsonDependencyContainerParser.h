//
// Created by xac1k on 6/4/26.
//

#ifndef YEAR_STUDY_WORK_JSONDEPENDENCYCONTAINERPARSER_H
#define YEAR_STUDY_WORK_JSONDEPENDENCYCONTAINERPARSER_H
#include <crow/json.h>

#include "IDependencyContainerParser.h"



class JsonDependencyContainerParser : public IDependencyContainerParser<crow::json::rvalue> {
public:
    std::shared_ptr<DependencyContainer> Parse(crow::json::rvalue source) override;
};


#endif //YEAR_STUDY_WORK_JSONDEPENDENCYCONTAINERPARSER_H