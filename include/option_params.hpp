#pragma once

struct OptionParams {
    double S0;        // Initial stock price
    double K;         // Strike price
    double T;         // Time to expiration (years)
    double r;         // Risk-free rate
    double sigma;     // Volatility
    bool isCall;      // true = call, false = put
};
