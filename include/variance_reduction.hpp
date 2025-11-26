#pragma once
#include "option_params.hpp"

class VarianceReduction {
public:
    static double antitheticVariates(const OptionParams& params, int numPaths);
};
