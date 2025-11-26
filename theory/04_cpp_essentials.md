# C++ Essentials for Monte Carlo Pricer

## Coming from Python/JavaScript

### Type System

**Python/JS**: Dynamic typing
```python
x = 5
x = "hello"  # OK
```

**C++**: Static typing
```cpp
int x = 5;
x = "hello";  // ERROR! x is an integer
```

### Basic Types

```cpp
int count = 1000000;           // Integer
double price = 100.5;          // Decimal number (use for money)
float vol = 0.2f;              // Smaller decimal (less precision)
bool isCall = true;            // Boolean
char letter = 'A';             // Single character
std::string name = "AAPL";     // String (need #include <string>)
```

### Functions

```cpp
// Return type, function name, parameter types
double calculatePayoff(double stockPrice, double strike, bool isCall) {
    if (isCall) {
        return std::max(stockPrice - strike, 0.0);
    } else {
        return std::max(strike - stockPrice, 0.0);
    }
}

// Void function (returns nothing)
void printPrice(double price) {
    std::cout << "Price: $" << price << std::endl;
}
```

### Structs (like JS objects)

```cpp
struct OptionParams {
    double S0;        // Initial stock price
    double K;         // Strike price
    double T;         // Time to expiration
    double r;         // Risk-free rate
    double sigma;     // Volatility
    bool isCall;      // Call or put
};

// Usage
OptionParams params;
params.S0 = 100.0;
params.K = 105.0;
// ... or ...
OptionParams params = {100.0, 105.0, 1.0, 0.05, 0.2, true};
```

### Vectors (like Python lists)

```cpp
#include <vector>

std::vector<double> prices;        // Empty vector
prices.push_back(100.0);           // Add element
prices.push_back(101.5);

std::vector<double> prices(1000);  // Pre-allocate 1000 elements
prices[0] = 100.0;                 // Access by index

// Iterate
for (size_t i = 0; i < prices.size(); i++) {
    std::cout << prices[i] << std::endl;
}

// Range-based for loop (like Python)
for (double price : prices) {
    std::cout << price << std::endl;
}
```

### Classes (structs with functions)

```cpp
class MonteCarloPricer {
private:
    // Private members (only accessible inside class)
    int numPaths;
    
public:
    // Constructor
    MonteCarloPricer(int paths) : numPaths(paths) {}
    
    // Member function
    double priceOption(const OptionParams& params) {
        // Implementation here
        return 0.0;
    }
};

// Usage
MonteCarloPricer pricer(100000);
double price = pricer.priceOption(params);
```

## Essential Libraries

### Math Functions
```cpp
#include <cmath>

double x = std::sqrt(2.0);      // Square root
double y = std::exp(1.0);       // e^x
double z = std::log(10.0);      // Natural log
double w = std::pow(2.0, 3.0);  // 2^3 = 8
double m = std::max(5.0, 3.0);  // Maximum
```

### Random Numbers
```cpp
#include <random>

std::random_device rd;                           // Seed
std::mt19937 gen(rd());                          // Generator
std::normal_distribution<double> dist(0.0, 1.0); // N(0,1)

double randomZ = dist(gen);  // Generate random number
```

### Input/Output
```cpp
#include <iostream>

std::cout << "Hello" << std::endl;  // Print to console

int x;
std::cin >> x;  // Read from console
```

## Compilation

### Single File
```bash
g++ main.cpp -o pricer
./pricer
```

### Multiple Files
```bash
g++ main.cpp monte_carlo.cpp -o pricer -std=c++17
```

### With Optimization
```bash
g++ main.cpp -o pricer -O3 -std=c++17
```

Flags:
- `-O3`: Maximum optimization (makes code faster)
- `-std=c++17`: Use C++17 standard
- `-Wall`: Show all warnings
- `-g`: Include debug information

## Common Patterns for This Project

### Pass by Reference (avoid copying)
```cpp
// Bad: Copies the entire struct
double price(OptionParams params) { ... }

// Good: Passes reference (no copy)
double price(const OptionParams& params) { ... }
```

### Const Correctness
```cpp
// const = promise not to modify
double calculatePayoff(const double stockPrice, const double strike) {
    // Can't modify stockPrice or strike
    return std::max(stockPrice - strike, 0.0);
}
```

### Header Files (.hpp) vs Implementation (.cpp)

**monte_carlo.hpp** (declarations):
```cpp
#pragma once  // Include guard

class MonteCarloPricer {
public:
    double priceOption(const OptionParams& params);
};
```

**monte_carlo.cpp** (implementation):
```cpp
#include "monte_carlo.hpp"

double MonteCarloPricer::priceOption(const OptionParams& params) {
    // Implementation here
    return 0.0;
}
```

## Memory Management (Brief)

Unlike Python/JS, C++ doesn't have automatic garbage collection.

**Stack allocation** (automatic, preferred):
```cpp
double price = 100.0;  // Automatically cleaned up
std::vector<double> prices(1000);  // Also automatic
```

**Heap allocation** (manual, avoid for now):
```cpp
double* price = new double(100.0);  // Manual allocation
delete price;  // Must manually free
```

For this project, stick with stack allocation and std::vector.

---
**Next**: Read `05_parallelization.md` when you're ready to optimize
