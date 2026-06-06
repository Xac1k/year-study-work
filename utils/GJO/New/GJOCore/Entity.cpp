//
// Created by xac1k on 5/24/26.
//

#include "./Entity.h"
#include <utility>
#include <asm-generic/errno.h>

Entity::Entity(const Entity &e)
: m_points(e.m_points)
, m_energy(e.m_energy)
, m_mark(e.m_mark)
{}

Entity::Entity(const std::vector<Point3d> &points) {
    m_points = points;

    m_energy = 0.0;
    m_mark = 0.0;
}

Entity::Entity(Entity &&e) noexcept
: m_points(std::exchange(e.m_points, {}))
, m_energy(std::exchange(e.m_energy, 0))
, m_mark(std::exchange(e.m_mark, 0))
{}

Entity &Entity::operator=(const Entity &e) {
    m_points = e.m_points;
    m_energy = e.m_energy;
    m_mark = e.m_mark;
    return *this;
}

Entity &Entity::operator=(Entity &&e) noexcept {
    std::swap(m_points, e.m_points);
    std::swap(m_energy, e.m_energy);
    std::swap(m_mark, e.m_mark);
    return *this;
}

Entity &Entity::SetEnergy(const double &energy) {
    m_energy = energy;
    return *this;
}

Entity &Entity::SetEstimation(const double &mark) {
    m_mark = mark;
    return *this;
}

Entity Entity::operator*(const Entity &other) const {
    Entity result;
    for (size_t i = 0; i < m_points.size(); ++i) {
        result.m_points[i] = m_points[i] * other.m_points[i];
    }
    return result;
};

Entity Entity::Abs() const noexcept {
    Entity result;
    for (size_t i = 0; i < m_points.size(); ++i) {
        result.m_points[i] = m_points[i].abs();
    }
    return result;
}

Entity Entity::operator*(double i) const {
    for (auto p: m_points) {
        p = p * i;
    }
    return *this;
}

Entity Entity::operator/(const double &divisor) const {
    return *this * (1.f/divisor);
}

Entity Entity::operator-(const double &multiplier) const noexcept {
    Entity result;
    for (size_t i = 0; i < m_points.size(); ++i) {
        result.m_points[i] = m_points[i] * multiplier;
    }
    return result;
}

Entity Entity::operator+(const Entity &other) const noexcept {
    Entity result;
    for (size_t i = 0; i < m_points.size(); ++i) {
        result.m_points[i] = m_points[i] + other.m_points[i];
    }
    return result;
}

Entity Entity::operator-(const Entity &other) const noexcept {
    Entity result;
    for (size_t i = 0; i < m_points.size(); ++i) {
        result.m_points[i] = m_points[i] - other.m_points[i];
    }
    return result;
}

std::vector<Point3d> Entity::GetPoints() const {
    return m_points;
}

size_t Entity::GetSize() const {
    return m_points.size();
}

Point3d& Entity::operator[](size_t index) {
    return m_points[index];
}

double Entity::GetEnergy() const {
    return m_energy;
}

double Entity::GetEstimation() const {
    return m_mark;
}
