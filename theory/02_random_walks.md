# Options Pricing Theory - Part 2: Stock Price Modeling

## How Stock Prices Move

Stock prices don't move in predictable patterns. They follow a **random walk** with drift.

### Geometric Brownian Motion (GBM)

The standard model for stock prices:

```
S(t) = S₀ × exp((r - σ²/2)t + σ√t × Z)

Where:
- S(t) = Stock price at time t
- S₀ = Initial stock price
- r = Risk-free rate (drift)
- σ = Volatility (randomness)
- t = Time
- Z = Random number from standard normal distribution N(0,1)
```

### Why This Formula?

**Drift term: (r - σ²/2)t**
- Makes the stock grow on average at the risk-free rate
- The σ²/2 is a mathematical correction (Itô's lemma)

**Random term: σ√t × Z**
- Z is a random number (mean=0, std=1)
- σ controls how much randomness
- √t means uncertainty grows with square root of time

### Example Simulation

```
Initial: S₀ = $100, r = 5%, σ = 20%, T = 1 year

Path 1: Z = 0.5
S(1) = 100 × exp((0.05 - 0.20²/2)×1 + 0.20×√1×0.5)
     = 100 × exp(0.03 + 0.10)
     = 100 × exp(0.13)
     = $113.88

Path 2: Z = -1.2
S(1) = 100 × exp((0.05 - 0.02)×1 + 0.20×1×(-1.2))
     = 100 × exp(0.03 - 0.24)
     = 100 × exp(-0.21)
     = $81.06
```

## Monte Carlo Steps

1. **Generate random Z** from normal distribution
2. **Calculate S(T)** using GBM formula
3. **Calculate payoff**: max(S(T) - K, 0) for call
4. **Repeat** N times (e.g., 1 million)
5. **Average** all payoffs
6. **Discount** to present value: Price = e^(-rT) × Average

## Volatility (σ) - The Key Parameter

**Low volatility (σ = 10%)**:
- Stock moves in tight range
- Options are cheaper (less chance of big moves)

**High volatility (σ = 40%)**:
- Stock swings wildly
- Options are expensive (more chance of big payoffs)

## Risk-Neutral Pricing

Important concept: We use the risk-free rate (r) as the drift, not the actual expected return of the stock.

Why? In a risk-neutral world, all assets grow at r, and we can price by taking expectations.

This is a deep mathematical result (fundamental theorem of asset pricing).

---
**Next**: Read `03_monte_carlo_method.md` for implementation details
