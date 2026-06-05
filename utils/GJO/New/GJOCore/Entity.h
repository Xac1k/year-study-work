//
// Created by xac1k on 5/24/26.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include <vector>
#include "../Point.h"

class Entity {
public:
    Entity() = default;
    Entity(const std::vector<Point3d>& points);

    // Копирующий
    Entity(const Entity& e);
    Entity& operator=(const Entity& e);

    // Перемещающий
    Entity(Entity&& e) noexcept;
    Entity& operator=(Entity&& e) noexcept;

    Entity operator-(const Entity& other) const noexcept;
    Entity operator+(const Entity& other) const noexcept;
    Entity operator-(const double& multiplier) const noexcept;

    Entity operator*(const Entity& other) const;
    Entity operator*(double i) const;

    Entity operator/(const double& divisor) const;
    [[nodiscard]] Entity Abs() const noexcept;

    Entity& SetEnergy(const double& energy);
    Entity& SetEstimation(const double& mark);
    [[nodiscard]] double GetEnergy() const;
    [[nodiscard]] double GetEstimation() const;

    [[nodiscard]] std::vector<Point3d> GetPoints() const;
    [[nodiscard]] size_t GetSize() const;

    Point3d &operator[](size_t index);

    ~Entity()=default;
private:
    std::vector<Point3d> m_points = {};
    double m_energy = 0;
    double m_mark = 0;
};

inline Entity operator*(const double i, const Entity& entity) {
    return entity * i;
};

#endif //MAIN_ENTITY_H