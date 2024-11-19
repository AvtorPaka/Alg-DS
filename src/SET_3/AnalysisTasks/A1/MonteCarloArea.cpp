#include "MonteCarloArea.h"
#include <cstdint>
#include <vector>
#include <cmath>
#include <random>

std::vector<double> MonteCarloArea::GetCirclesMBR(const std::vector<Circle> &circles) {
    std::vector<double> mbr{INT32_MAX, -INT32_MAX, INT32_MAX, -INT32_MAX};

    for (uint32_t i = 0; i < circles.size(); ++i) {
        mbr[0] = std::min(circles[i].xCenter - circles[i].radius, mbr[0]);
        mbr[1] = std::max(circles[i].xCenter + circles[i].radius, mbr[1]);
        mbr[2] = std::min(circles[i].yCenter - circles[i].radius, mbr[2]);
        mbr[3] = std::max(circles[i].yCenter + circles[i].radius, mbr[3]);
    }

    return mbr;
}

double MonteCarloArea::GetMBRArea(const std::vector<double> &mbr) {
    return (std::abs(mbr[1] - mbr[0])) * (std::abs(mbr[3] - mbr[2]));
}

double MonteCarloArea::MonteCarloCirclesIntersectionArea(const std::vector<Circle> &circles, int32_t numOfPoints) {
    std::vector<double> mbr = GetCirclesMBR(circles);
    double mbrArea = GetMBRArea(mbr);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> xDist(mbr[0], mbr[1]);
    std::uniform_real_distribution<> yDist(mbr[2], mbr[3]);

    int32_t cntPointsInArea = 0;
    for (int32_t i = 0; i < numOfPoints; ++i) {
        std::pair<double, double> randomPoint = std::make_pair(xDist(gen), yDist(gen));

        if (circles[0].InCircle(randomPoint) && circles[1].InCircle(randomPoint) && circles[2].InCircle(randomPoint)) {
            cntPointsInArea++;
        }
    }

    return ((double) cntPointsInArea / numOfPoints) * mbrArea;
}