#ifndef IMPLEMENTATIONDATA_MONTECARLOAREA_H
#define IMPLEMENTATIONDATA_MONTECARLOAREA_H
#include <utility>

struct Circle {
public:
    double xCenter;
    double yCenter;
    double radius;

    explicit Circle(double x = 0.0, double y = 0.0, double r = 0.0) {
        this->xCenter= x;
        this->yCenter = y;
        this->radius = r;
    }

    bool InCircle(const std::pair<double, double>& point) const {
        return (std::pow((point.first - this->xCenter), 2.0) + std::pow((point.second - this->yCenter), 2.0)) <= std::pow(this->radius, 2.0);
    }

    ~Circle() = default;
};

class MonteCarloArea {
private:
    static std::vector<double> GetCirclesMBR(const std::vector<Circle>& circles);
public:
    static double GetMBRArea(const std::vector<double>& mbr);
    static double MonteCarloCirclesIntersectionArea(const std::vector<Circle>& circles, int32_t numOfPoints);
};


#endif //IMPLEMENTATIONDATA_MONTECARLOAREA_H
