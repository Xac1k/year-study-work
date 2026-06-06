//
// Created by xac1k on 6/4/26.
//

#ifndef YEAR_STUDY_WORK_ICONFIGPARSER_H
#define YEAR_STUDY_WORK_ICONFIGPARSER_H

#include "../../GJO/New/DependencyContainer.h"

template <typename T>
class IDependencyContainerParser{
public:
    virtual ~IDependencyContainerParser() = default;
    virtual std::shared_ptr<DependencyContainer> Parse(T source) =0;
};

#endif //YEAR_STUDY_WORK_ICONFIGPARSER_H
