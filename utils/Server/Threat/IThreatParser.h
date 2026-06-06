//
// Created by xac1k on 6/3/26.
//

#ifndef YEAR_STUDY_WORK_ITHREATPARSER_H
#define YEAR_STUDY_WORK_ITHREATPARSER_H
#include "../../GJO/New/GJOCore/Types.h"

template<typename T>
class IThreatParser {
public:
    virtual ~IThreatParser() = default;
    virtual SharedThreats Parse(const T& source)=0;
};


#endif //YEAR_STUDY_WORK_ITHREATPARSER_H