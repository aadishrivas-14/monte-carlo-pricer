# Parallelization Theory

## Why Parallelize?

Monte Carlo simulations are **embarrassingly parallel**:
- Each path simulation is independent
- No communication needed between paths
- Perfect for multi-core CPUs

**Example**: 1 million paths
- Single core: 1 second
- 8 cores: ~0.125 seconds (8x speedup)

## CPU Architecture Basics

Modern CPUs have multiple cores:
- Laptop: 4-8 cores
- Desktop: 8-16 cores
- Server: 32-128 cores

Each core can run independent tasks simultaneously.

## Parallelization Strategies

### 1. Thread-Based Parallelism

Split work across threads (one per core):

```
Total paths: 1,000,000
Cores: 8

Thread 1: Paths 0 - 124,999
Thread 2: Paths 125,000 - 249,999
Thread 3: Paths 250,000 - 374,999
...
Thread 8: Paths 875,000 - 999,999

Each thread:
- Has its own RNG
- Calculates its own sum
- No sharing during computation

Final step: Combine all sums
```

### 2. C++ Threading

```cpp
#include <thread>
#include <vector>

void simulatePaths(int start, int end, double& result) {
    // Simulate paths from start to end
    // Store result
}

int main() {
    int numThreads = 8;
    std::vector<std::thread> threads;
    std::vector<double> results(numThreads);
    
    // Launch threads
    for (int i = 0; i < numThreads; i++) {
        int start = i * (totalPaths / numThreads);
        int end = (i + 1) * (totalPaths / numThreads);
        threads.push_back(std::thread(simulatePaths, start, end, 
                                      std::ref(results[i])));
    }
    
    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }
    
    // Combine results
    double total = 0;
    for (double r : results) {
        total += r;
    }
}
```

## Critical Concepts

### Thread Safety

**Problem**: Multiple threads accessing shared data
```cpp
// DANGER: Race condition
double sum = 0;
void worker() {
    sum += payoff;  // Multiple threads writing to sum!
}
```

**Solution 1**: Each thread has its own sum
```cpp
void worker(double& mySum) {
    mySum += payoff;  // Each thread writes to different variable
}
```

**Solution 2**: Use mutex (lock)
```cpp
#include <mutex>
std::mutex mtx;

void worker() {
    mtx.lock();
    sum += payoff;
    mtx.unlock();
}
```

### Random Number Generation

**Problem**: std::mt19937 is NOT thread-safe

**Solution**: Each thread has its own generator
```cpp
void worker(int threadId) {
    std::mt19937 gen(seed + threadId);  // Different seed per thread
    std::normal_distribution<double> dist(0.0, 1.0);
    
    for (int i = 0; i < pathsPerThread; i++) {
        double Z = dist(gen);
        // ... simulate path
    }
}
```

## Performance Considerations

### Amdahl's Law

Not all code can be parallelized:
```
Speedup = 1 / (S + P/N)

S = Serial portion (can't parallelize)
P = Parallel portion
N = Number of cores
```

Example: 95% parallel, 5% serial, 8 cores
```
Speedup = 1 / (0.05 + 0.95/8) = 5.9x (not 8x!)
```

### Overhead

Creating threads has cost:
- Thread creation time
- Context switching
- Cache coherency

**Rule of thumb**: Only parallelize if work per thread > 10ms

### Load Balancing

Ensure each thread does equal work:
```cpp
// Good: Equal distribution
int pathsPerThread = totalPaths / numThreads;

// Handle remainder
int remainder = totalPaths % numThreads;
// Give extra paths to first 'remainder' threads
```

## OpenMP (Easier Alternative)

OpenMP simplifies parallelization:

```cpp
#include <omp.h>

double sum = 0;
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < numPaths; i++) {
    double payoff = simulatePath();
    sum += payoff;
}
```

Compile with: `g++ -fopenmp main.cpp -o pricer`

## SIMD (Single Instruction Multiple Data)

Process multiple values simultaneously:
- Modern CPUs can do 4-8 operations at once
- Requires aligned memory and specific patterns
- Advanced topic for later optimization

## Measuring Performance

```cpp
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

// Your code here

auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
std::cout << "Time: " << duration.count() << " ms" << std::endl;
```

## Parallelization Checklist

Before parallelizing:
1. ✓ Profile: Is this the bottleneck?
2. ✓ Verify: Does serial version work correctly?
3. ✓ Measure: Baseline performance

When parallelizing:
1. ✓ Thread-local RNG
2. ✓ No shared mutable state
3. ✓ Equal work distribution
4. ✓ Minimize synchronization

After parallelizing:
1. ✓ Verify: Same results as serial (within randomness)
2. ✓ Measure: Actual speedup
3. ✓ Test: Different thread counts

---
**Next**: Read `06_variance_reduction.md` for advanced techniques
