//
// Created by xac1k on 6/1/26.
//

#ifndef MAIN_ENTITYFACTORY_H
#define MAIN_ENTITYFACTORY_H
#include <memory>

#include "IEntityGenerator.h"

class EntityFactory {
public:
    void SetStrategy(const std::shared_ptr<IEntityGenerator>&);
    [[nodiscard]] std::vector<Entity> NewEntities(size_t, const Point3d&, const Point3d&) const;
protected:
    std::shared_ptr<IEntityGenerator> m_gen;
};


#endif //MAIN_ENTITYFACTORY_H