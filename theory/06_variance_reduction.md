# Variance Reduction Techniques

## The Problem

Monte Carlo error decreases as 1/√N:
- 10x more accurate → 100x more paths → 100x more time

**Better approach**: Reduce variance, get same accuracy with fewer paths

## 1. Antithetic Variates

### Concept
For every random Z, also simulate -Z:
- If Z = 0.5, also use Z = -0.5
- Paths are negatively correlated
- Reduces variance

### Why It Works
```
Path 1: Z = 1.5 → Stock goes up → High payoff
Path 2: Z = -1.5 → Stock goes down → Low payoff

Average is more stable than two random paths
```

### Implementation
```cpp
double sum = 0;
for (int i = 0; i < numPaths / 2; i++) {
    double Z = normal(gen);
    
    // Original path
    double S1 = S0 * exp((r - 0.5*sigma*sigma)*T + sigma*sqrt(T)*Z);
    double payoff1 = max(S1 - K, 0.0);
    
    // Antithetic path
    double S2 = S0 * exp((r - 0.5*sigma*sigma)*T + sigma*sqrt(T)*(-Z));
    double payoff2 = max(S2 - K, 0.0);
    
    sum += payoff1 + payoff2;
}
double avgPayoff = sum / numPaths;
```

### Effectiveness
- Typical variance reduction: 30-50%
- Equivalent to 2-4x more paths
- Almost no extra computation cost

## 2. Control Variates

### Concept
Use a correlated variable with known expected value to reduce variance.

For options: Use geometric average Asian option (has analytical solution)

### Formula
```
Improved estimate = MC_estimate + β(Known_value - MC_control)

Where β is chosen to minimize variance
```

### Example
```
Price European call (unknown exact value)
Also price geometric Asian call (known analytical value)

If MC gives Asian = $5.2, but true value = $5.0:
Adjust European estimate down by β × ($5.2 - $5.0)
```

### Implementation Sketch
```cpp
// Simulate both target and control
double targetPayoff = max(S_T - K, 0.0);
double controlPayoff = geometricAsianPayoff(path);

// After all simulations
double beta = covariance(target, control) / variance(control);
double adjustedPrice = avgTarget + beta * (knownControl - avgControl);
```

### Effectiveness
- Variance reduction: 50-90% (if good correlation)
- Requires analytical solution for control
- More complex to implement

## 3. Stratified Sampling

### Concept
Divide the probability space into strata and sample from each:

```
Instead of random Z from N(0,1):
- Divide into 10 equal probability regions
- Sample one Z from each region
- Ensures coverage of entire distribution
```

### Implementation
```cpp
int numStrata = 10;
for (int i = 0; i < numStrata; i++) {
    // Sample from stratum i
    double u = (i + uniform(0,1)) / numStrata;  // Uniform in [i/n, (i+1)/n]
    double Z = inverseNormalCDF(u);  // Convert to normal
    
    // Simulate path with this Z
    // ...
}
```

### Effectiveness
- Variance reduction: 20-40%
- Ensures better coverage of sample space
- Slightly more complex RNG

## 4. Importance Sampling

### Concept
Sample more frequently from important regions:
- For deep out-of-the-money options, most paths have zero payoff
- Waste of computation!
- Instead, bias sampling toward profitable regions
- Correct with weights

### Formula
```
E[f(X)] = E[f(X) × w(X)]

Where w(X) is the likelihood ratio
```

### When to Use
- Deep out-of-the-money options
- Rare event simulation
- Tail risk estimation

### Complexity
- Requires careful weight calculation
- Can increase variance if done wrong
- Advanced technique

## 5. Quasi-Monte Carlo (QMC)

### Concept
Replace random numbers with low-discrepancy sequences:
- Sobol sequences
- Halton sequences
- Better coverage than random

### Properties
```
Random: Error ~ 1/√N
QMC: Error ~ 1/N (or better)
```

### Implementation
```cpp
#include <sobol.hpp>  // External library

SobolGenerator sobol(dimension);
for (int i = 0; i < numPaths; i++) {
    double u = sobol.next();
    double Z = inverseNormalCDF(u);
    // Simulate path
}
```

### Effectiveness
- Convergence rate: O(1/N) vs O(1/√N)
- Best for low-dimensional problems
- Requires specialized libraries

## Comparison Table

| Technique | Variance Reduction | Complexity | Extra Cost |
|-----------|-------------------|------------|------------|
| Antithetic | 30-50% | Low | ~0% |
| Control Variates | 50-90% | Medium | ~10% |
| Stratified | 20-40% | Medium | ~5% |
| Importance | Varies | High | ~20% |
| QMC | 10x-100x | Medium | ~0% |

## Practical Recommendations

### Start with Antithetic Variates
- Easy to implement
- Always helps
- No downside

### Add Control Variates if:
- You have a good control variable
- High correlation with target
- Worth the complexity

### Use QMC for:
- Production systems
- Low-dimensional problems (< 10 dimensions)
- When you need maximum accuracy

### Avoid Importance Sampling unless:
- You're an expert
- Dealing with rare events
- Standard MC completely fails

## Combining Techniques

You can combine multiple techniques:
```cpp
// Antithetic + Control Variates
for (int i = 0; i < numPaths / 2; i++) {
    double Z = normal(gen);
    
    // Simulate both antithetic paths
    // Calculate both target and control payoffs
    // Apply control variate correction
}
```

## Measuring Effectiveness

```cpp
// Calculate standard error
double variance = 0;
for (double payoff : payoffs) {
    variance += (payoff - mean) * (payoff - mean);
}
variance /= (payoffs.size() - 1);
double stdError = sqrt(variance / payoffs.size());

// Compare: Standard MC vs Variance Reduction
std::cout << "Standard MC SE: " << standardSE << std::endl;
std::cout << "Reduced SE: " << reducedSE << std::endl;
std::cout << "Improvement: " << standardSE / reducedSE << "x" << std::endl;
```

---
**Next**: Start implementing! Begin with `examples/01_basic_pricer.cpp`
