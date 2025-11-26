#pragma once
#include "option_params.hpp"

class MonteCarloBasic {
public:
    static double priceEuropeanOption(const OptionParams& params, int numPaths);
};
