#include "../include/black_scholes.hpp"
#include <cmath>

// Helper function: Cumulative normal distribution
static double normalCDF(double x)
{
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

double BlackScholes::priceEuropeanOption(const OptionParams &params)
{
    double S0 = params.S0;
    double K = params.K;
    double T = params.T;
    double r = params.r;
    double sigma = params.sigma;

    // 1. Calculate d1 and d2

    double d1 = (std::log(S0 / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    // 2. Use normalCDF() for N(d1) and N(d2)
    if (params.isCall)
    {
        return S0 * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
    }
    else
    {
        // Put
        return K * std::exp(-r * T) * normalCDF(-d2) - S0 * normalCDF(-d1);
    }
    // 3. Different formula for call vs put
    return 0.0;
}
