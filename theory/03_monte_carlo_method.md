# Options Pricing Theory - Part 3: Monte Carlo Method

## The Algorithm

```
Input: S₀, K, T, r, σ, N (number of paths)

1. Initialize sum = 0

2. For i = 1 to N:
   a. Generate random Z ~ N(0,1)
   b. Calculate S_T = S₀ × exp((r - σ²/2)T + σ√T × Z)
   c. Calculate payoff = max(S_T - K, 0)  // for call option
   d. Add payoff to sum

3. Average payoff = sum / N

4. Option price = e^(-rT) × Average payoff
```

## Why It Works: Law of Large Numbers

As N → ∞, the sample average converges to the true expected value.

**Convergence rate**: Error decreases as 1/√N
- 100 paths → Error ∝ 1/10
- 10,000 paths → Error ∝ 1/100
- 1,000,000 paths → Error ∝ 1/1000

To reduce error by 10x, you need 100x more paths!

## Random Number Generation

### Standard Normal Distribution N(0,1)

Properties:
- Mean = 0
- Standard deviation = 1
- Bell curve shape
- ~68% of values between -1 and 1
- ~95% of values between -2 and 2

### In C++
```cpp
#include <random>

std::mt19937 generator(seed);  // Mersenne Twister RNG
std::normal_distribution<double> normal(0.0, 1.0);

double Z = normal(generator);  // Generate random Z
```

## Measuring Accuracy

**Standard Error**: 
```
SE = σ_payoff / √N

Where σ_payoff is the standard deviation of payoffs
```

**95% Confidence Interval**:
```
Price ± 1.96 × SE
```

Example:
- Average payoff = $10
- Std dev of payoffs = $20
- N = 10,000 paths
- SE = 20 / √10,000 = 0.20
- 95% CI = $10 ± $0.39

## Practical Considerations

### How Many Paths?

- **Quick estimate**: 10,000 paths
- **Production pricing**: 100,000 - 1,000,000 paths
- **Research/calibration**: 10,000,000+ paths

Trade-off: Accuracy vs computation time

### Seed Management

Always set a seed for reproducibility:
```cpp
std::mt19937 generator(12345);  // Fixed seed
```

For production, use random seed:
```cpp
std::random_device rd;
std::mt19937 generator(rd());
```

## Verification

Always verify against known solutions:

**Black-Scholes Formula** (analytical solution for European options):
```
C = S₀N(d₁) - Ke^(-rT)N(d₂)

d₁ = [ln(S₀/K) + (r + σ²/2)T] / (σ√T)
d₂ = d₁ - σ√T

N(x) = cumulative standard normal distribution
```

Your Monte Carlo price should match Black-Scholes within the standard error.

---
**Next**: Read `04_cpp_essentials.md` for C++ concepts needed
