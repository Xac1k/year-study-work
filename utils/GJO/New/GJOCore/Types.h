//
// Created by xac1k on 5/27/26.
//

#ifndef MAIN_TYPES_H
#define MAIN_TYPES_H
#include <memory>

#include "Entity.h"
#include "../Threat.h"

using Entities = std::vector<Entity>;
using SharedEntity = std::shared_ptr<Entity>;
using SharedThreat = std::shared_ptr<IThreat>;
using SharedEntities = std::vector<SharedEntity>;
using SharedThreats = std::vector<SharedThreat>;

#endif //MAIN_TYPES_H