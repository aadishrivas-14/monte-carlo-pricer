# Options Pricing Theory - Part 1: Basics

## What is an Option?

An **option** is a financial contract that gives the buyer the RIGHT (not obligation) to buy or sell an asset at a predetermined price on or before a specific date.

### Key Terms

- **Underlying Asset (S)**: The stock/asset the option is based on (e.g., Apple stock)
- **Strike Price (K)**: The price at which you can buy/sell the asset
- **Expiration Date (T)**: When the option expires
- **Premium**: What you pay today to buy the option

### Types of Options

**Call Option**: Right to BUY the asset at strike price K
- You profit when stock price goes UP above K

**Put Option**: Right to SELL the asset at strike price K  
- You profit when stock price goes DOWN below K

## Payoff Diagrams

### Call Option Payoff at Expiration
```
If Stock Price (S_T) > Strike (K):
    Payoff = S_T - K
Else:
    Payoff = 0

Example: K = $100
- Stock at $120 → Payoff = $20
- Stock at $105 → Payoff = $5
- Stock at $95 → Payoff = $0
```

### Put Option Payoff at Expiration
```
If Stock Price (S_T) < Strike (K):
    Payoff = K - S_T
Else:
    Payoff = 0

Example: K = $100
- Stock at $80 → Payoff = $20
- Stock at $95 → Payoff = $5
- Stock at $105 → Payoff = $0
```

## The Pricing Problem

**Question**: How much should you pay TODAY for an option that expires in the FUTURE?

**Inputs Needed**:
1. **S₀**: Current stock price (e.g., $100)
2. **K**: Strike price (e.g., $105)
3. **T**: Time to expiration in years (e.g., 0.25 = 3 months)
4. **r**: Risk-free interest rate (e.g., 0.05 = 5% per year)
5. **σ**: Volatility - how much the stock price fluctuates (e.g., 0.20 = 20%)

**Output**: Fair option price today

## Why Monte Carlo?

Since we don't know the future stock price, we:
1. Simulate thousands of possible future price paths
2. Calculate the payoff for each path
3. Average all payoffs
4. Discount back to today's value

This gives us the expected option price.

## European vs American Options

**European Option**: Can only be exercised at expiration
- Easier to price
- We'll start with these

**American Option**: Can be exercised anytime before expiration
- More complex to price
- Requires different techniques

---
**Next**: Read `02_random_walks.md` to understand how stock prices move
