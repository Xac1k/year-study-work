//
// Created by xac1k on 4/28/26.
//

#include "Threat.h"

std::tuple<double, double, double> GJO::Drone::RadarThreat::GetPoint() const {
    return std::make_tuple(m_x, m_y, m_z);
}

double GJO::Drone::RadarThreat::GetRadius() const {
    return m_radius;
}

GJO::Drone::RadarThreat &GJO::Drone::RadarThreat::SetRadius(double r) {
    m_radius = r;
    return *this;
}

GJO::Drone::RadarThreat &GJO::Drone::RadarThreat::SetPoint(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
    return *this;
}

double GJO::Drone::RadarThreat::operator()(const double &x, const double &y, const double &z) {
    return 0; //TODO: Реализовать функцию угроз для радаров в зависимости от точки пространства
}

double GJO::Drone::AirDefenseThreat::operator()(const double &x, const double &y, const double &z) {
    return 0; //TODO: Реализовать функцию угроз для ПВО в зависимости от точки пространства
}

GJO::Drone::AirDefenseThreat &GJO::Drone::AirDefenseThreat::SetPoint(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
    return *this;
}

GJO::Drone::AirDefenseThreat &GJO::Drone::AirDefenseThreat::SetRadius(double r) {
    m_radius = r;
    return *this;
}

double GJO::Drone::AirDefenseThreat::GetHeight() const {
    return m_height;
}

double GJO::Drone::AirDefenseThreat::GetRadius() const {
    return m_radius;
}

std::tuple<double, double, double> GJO::Drone::AirDefenseThreat::GetPoint() const {
    return std::make_tuple(m_x, m_y, m_z);
}

GJO::Drone::AirDefenseThreat &GJO::Drone::AirDefenseThreat::SetHeight(double h) {
    m_height = h;
    return *this;
}


