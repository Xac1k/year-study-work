//
// Created by xac1k on 6/1/26.
//

#include "./EntityFactory.h"

void EntityFactory::SetStrategy(const std::shared_ptr<IEntityGenerator>& gen){
    m_gen = gen;
}

std::vector<Entity> EntityFactory::NewEntities(const size_t count, const Point3d& start, const Point3d& end) const {
    if (m_gen == nullptr)
        throw std::runtime_error("EntityFactory::NewEntities(): entity generator isn't set upped.");

    std::vector<Entity> result;
    for (size_t index = 0; index < count; index++)
        result.push_back(m_gen->Generate(start, end));

    return result;
}