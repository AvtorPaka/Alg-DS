#ifndef IMPLEMENTATIONDATA_EXAMPLETESTS_H
#define IMPLEMENTATIONDATA_EXAMPLETESTS_H

#include "MonteCarloArea.h"
#include <vector>

class ExampleTests {
private:
    static double MonteCarloCirclesIntersectionAreaSmall(const std::vector<Circle> &circles, int32_t numOfPoints);
public:
    static void TestLargeMBR(const std::string& pathToDataFile);
    static void TestSmallMBR(const std::string& pathToDataFile);
};

#endif //IMPLEMENTATIONDATA_EXAMPLETESTS_H
