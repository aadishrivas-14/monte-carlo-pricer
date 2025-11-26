#pragma once
#include "option_params.hpp"

class BlackScholes {
public:
    static double priceEuropeanOption(const OptionParams& params);
};
