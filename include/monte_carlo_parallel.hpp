#pragma once
#include "option_params.hpp"

class MonteCarloParallel {
public:
    static double priceEuropeanOption(const OptionParams& params, int numPaths, int numThreads);
};
