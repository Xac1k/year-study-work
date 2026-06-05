//
// Created by xac1k on 4/28/26.
//

#ifndef MAIN_THREAT_H
#define MAIN_THREAT_H
#include <tuple>


namespace GJO::Drone {
    class IThreat {
    public:
        virtual ~IThreat();

        // Вычисляем коэффициент угрозы от точки
        virtual double operator()(const double& x, const double& y, const double& z) = 0;
    };

    class RadarThreat : public IThreat {
    public:
        double operator()(const double& x, const double& y, const double& z) override;
        RadarThreat& SetPoint(double x, double y, double z);
        RadarThreat& SetRadius(double r);
        [[nodiscard]] double GetRadius() const;
        [[nodiscard]] std::tuple<double,double,double> GetPoint() const;
    private:
        double m_x = 0, m_y = 0, m_z = 0;
        double m_radius = 0;
    };

    class AirDefenseThreat : public IThreat {
    public:
        double operator()(const double& x, const double& y, const double& z) override;
        AirDefenseThreat& SetPoint(double x, double y, double z);
        AirDefenseThreat& SetRadius(double r);
        AirDefenseThreat& SetHeight(double h);
        [[nodiscard]] std::tuple<double,double,double> GetPoint() const;
        [[nodiscard]] double GetRadius() const;
        [[nodiscard]] double GetHeight() const;
    private:
        double m_x = 0, m_y = 0, m_z = 0;
        double m_radius = 0;
        double m_height = 0;
    };
}


#endif //MAIN_THREAT_H