# Quick Start Guide

## Project Structure
```
monte-carlo-pricer/
├── theory/                    # Read these first!
│   ├── 01_options_basics.md
│   ├── 02_random_walks.md
│   ├── 03_monte_carlo_method.md
│   ├── 04_cpp_essentials.md
│   ├── 05_parallelization.md
│   └── 06_variance_reduction.md
├── include/                   # Header files
│   ├── option_params.hpp
│   ├── black_scholes.hpp
│   ├── monte_carlo_basic.hpp
│   ├── monte_carlo_parallel.hpp
│   └── variance_reduction.hpp
├── src/                       # Implementation files (YOU WRITE THESE)
│   ├── black_scholes.cpp
│   ├── monte_carlo_basic.cpp
│   ├── monte_carlo_parallel.cpp
│   └── variance_reduction.cpp
├── examples/                  # Test programs
│   ├── 01_basic_pricer.cpp
│   ├── 02_parallel_pricer.cpp
│   └── 03_variance_reduction.cpp
├── Makefile                   # Build system
└── IMPLEMENTATION_GUIDE.md    # Detailed step-by-step guide
```

## Learning Path

### Day 1: Theory + Setup
1. Read `theory/01_options_basics.md` (15 min)
2. Read `theory/02_random_walks.md` (20 min)
3. Read `theory/03_monte_carlo_method.md` (20 min)
4. Read `theory/04_cpp_essentials.md` (30 min)

### Day 2: First Implementation
1. Implement `src/black_scholes.cpp`
2. Implement `src/monte_carlo_basic.cpp`
3. Test: `make run1`
4. Verify: Should match Black-Scholes within 1%

### Day 3-4: Parallelization
1. Read `theory/05_parallelization.md`
2. Implement `src/monte_carlo_parallel.cpp`
3. Test: `make run2`
4. Benchmark: Should see 4-8x speedup

### Day 5-6: Variance Reduction
1. Read `theory/06_variance_reduction.md`
2. Implement `src/variance_reduction.cpp`
3. Test: `make run3`
4. Compare: Lower variance than basic MC

## Build Commands

```bash
# Build all examples
make

# Build and run specific example
make run1    # Basic pricer
make run2    # Parallel pricer
make run3    # Variance reduction

# Clean build artifacts
make clean
```

## Your First Task

1. Open `theory/01_options_basics.md`
2. Read and understand call/put options
3. Then open `IMPLEMENTATION_GUIDE.md`
4. Start with Phase 1, Step 1

## Getting Unstuck

**If theory is confusing:**
- Draw diagrams on paper
- Work through numerical examples
- Watch YouTube videos on the topic

**If code won't compile:**
- Check error message carefully
- Verify all #include statements
- Make sure using C++17: `g++ -std=c++17`

**If results are wrong:**
- Print intermediate values
- Test with small numPaths (100) first
- Compare each step with theory

**If performance is poor:**
- Check optimization flag: `-O3`
- Profile with `time ./build/01_basic_pricer`
- Ensure not doing unnecessary work in loop

## Success Criteria

You'll know you're done when:
- [ ] Basic MC matches Black-Scholes within 1%
- [ ] Parallel version is 4-8x faster
- [ ] Antithetic variates reduces variance by 30-50%
- [ ] You understand WHY each technique works

## What You'll Learn

**Options Pricing:**
- How options work
- Monte Carlo simulation
- Risk-neutral pricing

**C++ Programming:**
- Random number generation
- Multi-threading
- Performance optimization
- Memory management

**Computational Finance:**
- Variance reduction
- Convergence analysis
- Numerical methods

## Next Steps After Completion

1. Add more option types (Asian, Barrier)
2. Implement Greeks (delta, gamma, vega)
3. Add control variates
4. Try GPU acceleration (CUDA)
5. Build a pricing library

---

**Ready?** Start with `theory/01_options_basics.md`!
