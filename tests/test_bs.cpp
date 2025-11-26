#include <iostream>
#include <iomanip>
#include "../include/option_params.hpp"
#include "../include/black_scholes.hpp"

int main() {
    std::cout << "=== Black-Scholes Option Pricer Tests ===" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << std::endl;
    
    // Test 1: At-the-money call
    std::cout << "Test 1: At-the-money Call" << std::endl;
    OptionParams test1 = {100.0, 100.0, 1.0, 0.05, 0.20, true};
    std::cout << "  S=$100, K=$100, T=1yr, r=5%, σ=20%" << std::endl;
    std::cout << "  Price: $" << BlackScholes::priceEuropeanOption(test1) << std::endl;
    std::cout << std::endl;
    
    // Test 2: In-the-money call
    std::cout << "Test 2: In-the-money Call" << std::endl;
    OptionParams test2 = {110.0, 100.0, 1.0, 0.05, 0.20, true};
    std::cout << "  S=$110, K=$100, T=1yr, r=5%, σ=20%" << std::endl;
    std::cout << "  Price: $" << BlackScholes::priceEuropeanOption(test2) << std::endl;
    std::cout << std::endl;
    
    // Test 3: Out-of-the-money call
    std::cout << "Test 3: Out-of-the-money Call" << std::endl;
    OptionParams test3 = {90.0, 100.0, 1.0, 0.05, 0.20, true};
    std::cout << "  S=$90, K=$100, T=1yr, r=5%, σ=20%" << std::endl;
    std::cout << "  Price: $" << BlackScholes::priceEuropeanOption(test3) << std::endl;
    std::cout << std::endl;
    
    // Test 4: High volatility
    std::cout << "Test 4: High Volatility Call" << std::endl;
    OptionParams test4 = {100.0, 100.0, 1.0, 0.05, 0.40, true};
    std::cout << "  S=$100, K=$100, T=1yr, r=5%, σ=40%" << std::endl;
    std::cout << "  Price: $" << BlackScholes::priceEuropeanOption(test4) << std::endl;
    std::cout << std::endl;
    
    // Test 5: Short expiration
    std::cout << "Test 5: Short Expiration Call" << std::endl;
    OptionParams test5 = {100.0, 100.0, 0.25, 0.05, 0.20, true};
    std::cout << "  S=$100, K=$100, T=3mo, r=5%, σ=20%" << std::endl;
    std::cout << "  Price: $" << BlackScholes::priceEuropeanOption(test5) << std::endl;
    std::cout << std::endl;
    
    // Test 6: Put option
    std::cout << "Test 6: At-the-money Put" << std::endl;
    OptionParams test6 = {100.0, 100.0, 1.0, 0.05, 0.20, false};
    std::cout << "  S=$100, K=$100, T=1yr, r=5%, σ=20%" << std::endl;
    std::cout << "  Price: $" << BlackScholes::priceEuropeanOption(test6) << std::endl;
    std::cout << std::endl;
    
    // Test 7: Deep in-the-money call (should be close to S-K)
    std::cout << "Test 7: Deep In-the-money Call" << std::endl;
    OptionParams test7 = {150.0, 100.0, 1.0, 0.05, 0.20, true};
    std::cout << "  S=$150, K=$100, T=1yr, r=5%, σ=20%" << std::endl;
    std::cout << "  Price: $" << BlackScholes::priceEuropeanOption(test7) << std::endl;
    std::cout << "  (Should be close to $50)" << std::endl;
    std::cout << std::endl;
    
    return 0;
}
