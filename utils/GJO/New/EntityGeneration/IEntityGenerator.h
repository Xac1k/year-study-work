//
// Created by xac1k on 6/1/26.
//

#ifndef MAIN_IENTITYGENERATOR_H
#define MAIN_IENTITYGENERATOR_H
#include "../GJOCore/Entity.h"


class IEntityGenerator {
public:
    virtual ~IEntityGenerator()=default;
    virtual Entity Generate(const Point3d& startPoint, const Point3d& endPoint)=0;
};


#endif //MAIN_IENTITYGENERATOR_H