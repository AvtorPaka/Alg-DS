#include "ExampleTests.h"

#include <iostream>
#include <cstdint>
#include <fstream>
#include <numbers>
#include <cmath>
#include <random>

void ExampleTests::TestSmallMBR(const std::string& pathToDataFile) {
    double circleNewRadius = std::sqrt(5) / 2;
    std::vector<Circle> circles{Circle(1, 1, 1), Circle(1.5, 2, circleNewRadius), Circle(2, 1.5, circleNewRadius)};

    std::ofstream dataFile(pathToDataFile);
    double actualSquare = std::numbers::pi * 0.25 + 1.25 * std::asin(0.8) - 1;
    dataFile << "Tests results with small minimal bounding rectangle\nA_a (accurate area) = " + std::to_string(actualSquare) + '\n';
    dataFile << "N - number of random points\nA_p - monte carlo approximate area\nD - deviation from accurate area\n\nN : A_p : D\n";
    int32_t numOfIterations = 100;


    for (int32_t i = numOfIterations; i <= 100000; i += 500) {
        double curApproxArea = MonteCarloCirclesIntersectionAreaSmall(circles, i);
        std::string dataString =
                std::to_string(i) + " : " + std::to_string(curApproxArea) + " : " +
                std::to_string(std::abs(actualSquare - curApproxArea)) + '\n';
        dataFile << dataString;
    }

    dataFile.close();
}

void ExampleTests::TestLargeMBR(const std::string &pathToDataFile) {
    double circleNewRadius = std::sqrt(5) / 2;
    std::vector<Circle> circles{Circle(1, 1, 1), Circle(1.5, 2, circleNewRadius), Circle(2, 1.5, circleNewRadius)};

    std::ofstream dataFile(pathToDataFile);
    double actualSquare = std::numbers::pi * 0.25 + 1.25 * std::asin(0.8) - 1;
    dataFile << "Tests results with large minimal bounding rectangle\nA_a (accurate area) = " + std::to_string(actualSquare) + '\n';
    dataFile << "N - number of random points\nA_p - monte carlo approximate area\nD - deviation from accurate area\n\nN : A_p : D\n";
    int32_t numOfIterations = 100;


    for (int32_t i = numOfIterations; i <= 100000; i += 500) {
        double curApproxArea = MonteCarloArea::MonteCarloCirclesIntersectionArea(circles, i);
        std::string dataString =
                std::to_string(i) + " : " + std::to_string(curApproxArea) + " : " +
                std::to_string(std::abs(actualSquare - curApproxArea)) + '\n';
        dataFile << dataString;
    }

    dataFile.close();
}


double ExampleTests::MonteCarloCirclesIntersectionAreaSmall(const std::vector<Circle> &circles, int32_t numOfPoints) {
    double circleNewRadius = std::sqrt(5) / 2;
    std::vector<double> mbr{2 - circleNewRadius, 2.2, 1.5 - circleNewRadius, 2.2};
    double mbrArea = MonteCarloArea::GetMBRArea(mbr);

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