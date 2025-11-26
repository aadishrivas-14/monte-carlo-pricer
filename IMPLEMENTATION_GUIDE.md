# Implementation Guide - Step by Step

## Prerequisites
1. Read theory files in order:
   - `theory/01_options_basics.md` - Understand what you're pricing
   - `theory/02_random_walks.md` - How stock prices move
   - `theory/03_monte_carlo_method.md` - The algorithm
   - `theory/04_cpp_essentials.md` - C++ concepts needed

## Phase 1: Basic Monte Carlo (Days 1-2)

### Step 1: Implement Black-Scholes (for verification)
**File**: `src/black_scholes.cpp`

This gives you the "correct answer" to verify your Monte Carlo.

**What to implement**:
```cpp
double BlackScholes::priceEuropeanOption(const OptionParams& params) {
    // Implement the Black-Scholes formula
    // See theory/03_monte_carlo_method.md for formula
}
```

**Test**: Run with known values, verify against online calculators

### Step 2: Implement Basic Monte Carlo
**File**: `src/monte_carlo_basic.cpp`

**Algorithm**:
1. Create random number generator (std::mt19937)
2. Loop numPaths times:
   - Generate random Z from N(0,1)
   - Calculate S_T using GBM formula
   - Calculate payoff: max(S_T - K, 0) for call
   - Add to sum
3. Average = sum / numPaths
4. Discount: price = exp(-r*T) * average

**What to implement**:
```cpp
double MonteCarloBasic::priceEuropeanOption(const OptionParams& params, int numPaths) {
    // TODO: Your implementation here
}
```

**Test**: 
```bash
make run1
```
Should match Black-Scholes within ~1%

### Step 3: Measure Convergence
Modify example to test different path counts:
- 1,000 paths
- 10,000 paths
- 100,000 paths
- 1,000,000 paths

Observe: Error decreases as 1/√N

## Phase 2: Parallelization (Days 3-4)

### Step 4: Implement Multi-threaded Version
**File**: `src/monte_carlo_parallel.cpp`

**Read first**: `theory/05_parallelization.md`

**Algorithm**:
1. Divide numPaths by numThreads
2. Create vector of threads
3. Each thread:
   - Has its own RNG (different seed!)
   - Simulates its portion of paths
   - Stores result in thread-local variable
4. Join all threads
5. Combine results

**What to implement**:
```cpp
double MonteCarloParallel::priceEuropeanOption(const OptionParams& params, 
                                               int numPaths, 
                                               int numThreads) {
    // TODO: Your implementation here
}
```

**Test**:
```bash
make run2
```
Should see 4-8x speedup on modern CPU

### Step 5: Benchmark Different Thread Counts
Test with 1, 2, 4, 8, 16 threads
Plot speedup vs thread count

## Phase 3: Variance Reduction (Days 5-6)

### Step 6: Implement Antithetic Variates
**File**: `src/variance_reduction.cpp`

**Read first**: `theory/06_variance_reduction.md`

**Algorithm**:
1. Loop numPaths/2 times:
   - Generate Z
   - Simulate path with Z → payoff1
   - Simulate path with -Z → payoff2
   - Add both to sum
2. Average and discount

**What to implement**:
```cpp
double VarianceReduction::antitheticVariates(const OptionParams& params, int numPaths) {
    // TODO: Your implementation here
}
```

**Test**:
```bash
make run3
```
Run 10 times, compare standard deviation to basic MC

## Phase 4: Advanced (Optional)

### Step 7: GPU Acceleration
- Requires CUDA toolkit
- See README.md for CUDA implementation outline
- Advanced topic - only if you have NVIDIA GPU

### Step 8: Additional Option Types
- Asian options (path-dependent)
- Barrier options (knock-in/knock-out)
- Multi-asset options

## Debugging Tips

### Common Issues

**1. Price is way off**
- Check: Are you discounting? (multiply by exp(-r*T))
- Check: Correct payoff formula? max(S-K, 0) for call
- Check: Using correct volatility? (0.20, not 20)

**2. Parallel version gives different results**
- Expected! Monte Carlo is random
- Should be within standard error
- Check: Each thread has different RNG seed

**3. Compilation errors**
- Check: All #include statements correct
- Check: Using -std=c++17 flag
- Check: Linking with -pthread for threads

**4. Segmentation fault**
- Check: Vector sizes allocated correctly
- Check: Not accessing out of bounds
- Use debugger: `gdb ./build/01_basic_pricer`

## Verification Checklist

Before moving to next phase:
- [ ] Code compiles without warnings
- [ ] Matches Black-Scholes within 1%
- [ ] Tested with different parameters
- [ ] Measured performance
- [ ] Code is commented
- [ ] Committed to git

## Getting Help

If stuck:
1. Re-read relevant theory file
2. Check example code
3. Print intermediate values (S_T, payoffs)
4. Start with small numPaths (100) for debugging
5. Compare with online Monte Carlo calculators

## Success Metrics

**Phase 1**: 
- Basic MC works, matches BS within 1%
- Understand convergence rate

**Phase 2**:
- 4-8x speedup with parallelization
- Understand thread safety

**Phase 3**:
- 30-50% variance reduction with antithetic variates
- Same accuracy with fewer paths

## Next Steps After Completion

1. Add more option types (Asian, Barrier)
2. Implement control variates
3. Add Greeks calculation (delta, gamma, vega)
4. Build interactive CLI
5. Optimize with SIMD
6. GPU acceleration with CUDA

Good luck! Start with Phase 1, Step 1.
