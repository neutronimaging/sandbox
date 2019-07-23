#ifndef CROSSCORRELATION_H
#define CROSSCORRELATION_H

#include <algorithm>
#include <vector>
class CrossCorrelation
{
public:
    CrossCorrelation();
    float operator()(float *x, float *y, size_t N, bool parallel=false);

private:
    std::vector<float> computeSums(float *x, float *y, size_t N);
    std::vector<float> computeSumsParallel(float *x, float *y, size_t N);
    std::vector<float> mSums;
    size_t mN;
};

#endif // CROSSCORRELATION_H
