# Mentor Guide - Teaching Approach

## Your Role as Mentor

You're guiding someone who:
- Knows Python/JavaScript but not C++
- Has no options pricing background
- Wants to learn by doing
- Needs step-by-step guidance

## Teaching Philosophy

### 1. Theory Before Code
Never let them write code without understanding WHY.

**Bad**: "Just implement this formula"
**Good**: "Let's understand what this formula represents first"

### 2. Build Incrementally
Each step should work before moving to the next.

**Progression:**
1. Black-Scholes (analytical) → Verify understanding
2. Basic Monte Carlo → Verify correctness
3. Parallelization → Verify speedup
4. Variance reduction → Verify improvement

### 3. Learn from Mistakes
Encourage experimentation and debugging.

**When they get wrong results:**
- Don't give the answer immediately
- Ask: "What do you expect to see?"
- Guide: "Let's print intermediate values"
- Help them discover the bug

### 4. Connect to Intuition
Always relate math to real-world meaning.

**Example:**
- Not: "σ is the volatility parameter"
- But: "σ measures how much the stock price jumps around. Higher σ = more uncertainty = more valuable option"

## Session-by-Session Guide

### Session 1: Options Basics (1 hour)

**Goal**: Understand what they're pricing

**Activities:**
1. Draw payoff diagrams on paper
2. Work through numerical examples
3. Discuss: "Why would someone buy a call option?"
4. Assign: Read `theory/01_options_basics.md`

**Check understanding:**
- "If stock is $110 and strike is $100, what's the call payoff?"
- "When would you buy a put option?"

### Session 2: Random Walks (1 hour)

**Goal**: Understand stock price modeling

**Activities:**
1. Simulate a few paths by hand
2. Discuss: "Why exponential, not linear?"
3. Explain: Risk-neutral pricing (briefly)
4. Assign: Read `theory/02_random_walks.md`

**Check understanding:**
- "What happens if we increase volatility?"
- "Why do we use the risk-free rate?"

### Session 3: Monte Carlo Method (1 hour)

**Goal**: Understand the algorithm

**Activities:**
1. Walk through algorithm step-by-step
2. Do 5 paths by hand with calculator
3. Discuss: Convergence rate
4. Assign: Read `theory/03_monte_carlo_method.md`

**Check understanding:**
- "How many paths to reduce error by 10x?"
- "Why do we discount the payoff?"

### Session 4: C++ Crash Course (1.5 hours)

**Goal**: Learn enough C++ to implement

**Activities:**
1. Compare with Python/JS syntax
2. Write simple programs (hello world, loops)
3. Explain: Types, functions, structs
4. Assign: Read `theory/04_cpp_essentials.md`

**Check understanding:**
- Write a function that calculates payoff
- Create a struct with option parameters

### Session 5: Implement Black-Scholes (1 hour)

**Goal**: Get a working reference implementation

**Guide them through:**
1. Understanding the formula
2. Implementing normalCDF
3. Calculating d1 and d2
4. Testing with known values

**Common mistakes:**
- Forgetting to handle put options
- Using wrong log (log10 vs ln)
- Not checking for edge cases

### Session 6: Implement Basic Monte Carlo (2 hours)

**Goal**: First working Monte Carlo pricer

**Guide them through:**
1. Setting up RNG
2. Implementing the loop
3. Calculating S_T correctly
4. Discounting the result

**Common mistakes:**
- Not using exp() for GBM
- Forgetting to discount
- Wrong payoff formula
- Using volatility as percentage (20 instead of 0.20)

**Debugging approach:**
1. Print first 10 paths
2. Check: Are S_T values reasonable?
3. Check: Are payoffs correct?
4. Compare with Black-Scholes

### Session 7: Parallelization Theory (1 hour)

**Goal**: Understand multi-threading

**Activities:**
1. Explain: Cores, threads, parallelism
2. Discuss: Thread safety, race conditions
3. Draw: How work is divided
4. Assign: Read `theory/05_parallelization.md`

**Check understanding:**
- "Why does each thread need its own RNG?"
- "What happens if threads share a variable?"

### Session 8: Implement Parallel Version (2 hours)

**Goal**: Multi-threaded pricer

**Guide them through:**
1. Dividing work among threads
2. Creating thread-local RNG
3. Launching and joining threads
4. Combining results

**Common mistakes:**
- Sharing RNG across threads
- Race conditions on sum
- Not joining threads
- Wrong work distribution

**Testing:**
1. Verify: Same result as single-threaded (within randomness)
2. Measure: Speedup with different thread counts
3. Discuss: Why not perfect 8x speedup?

### Session 9: Variance Reduction (1.5 hours)

**Goal**: Implement antithetic variates

**Activities:**
1. Explain: Why it reduces variance
2. Show: Negative correlation
3. Implement together
4. Measure improvement

**Testing:**
1. Run 20 times, calculate std dev
2. Compare with basic MC
3. Discuss: When does it help most?

### Session 10: Review and Extensions (1 hour)

**Goal**: Consolidate learning

**Activities:**
1. Review all concepts
2. Discuss: What was hardest?
3. Explore: What's next?
4. Plan: Extensions to implement

## Guiding Principles

### When They're Stuck

**On Theory:**
- Use analogies and real-world examples
- Draw pictures and diagrams
- Work through numerical examples
- Break down into smaller concepts

**On Code:**
- Don't give the solution
- Ask: "What do you expect this line to do?"
- Suggest: "Let's print this variable"
- Guide: "What if we test with simpler inputs?"

### When They're Ahead

**Challenge them:**
- "Can you optimize this further?"
- "What if we price a different option type?"
- "How would you add error bars?"
- "Can you explain this to someone else?"

### When They're Frustrated

**Encourage:**
- "This is hard - you're learning a lot"
- "Let's take a break and come back"
- "Show me what you've tried so far"
- "Every bug you fix teaches you something"

## Red Flags

Watch for these issues:

**Conceptual:**
- Implementing without understanding
- Memorizing formulas without meaning
- Skipping verification steps
- Not testing edge cases

**Technical:**
- Ignoring compiler warnings
- Not using version control
- Copy-pasting without understanding
- Premature optimization

**Learning:**
- Rushing through theory
- Not asking questions
- Giving up too quickly
- Not experimenting

## Assessment Checkpoints

### After Basic MC:
- [ ] Can explain Monte Carlo in their own words
- [ ] Code matches Black-Scholes within 1%
- [ ] Understands convergence rate
- [ ] Can modify parameters and predict results

### After Parallelization:
- [ ] Can explain thread safety
- [ ] Achieves 4-8x speedup
- [ ] Understands Amdahl's law
- [ ] Can debug race conditions

### After Variance Reduction:
- [ ] Can explain why antithetic variates work
- [ ] Measures variance reduction correctly
- [ ] Understands trade-offs
- [ ] Can suggest other techniques

## Extension Ideas

Once core project is complete:

**Easy:**
- Add put options
- Add input validation
- Create interactive CLI
- Plot convergence graphs

**Medium:**
- Implement Asian options
- Add control variates
- Calculate Greeks
- Add more variance reduction techniques

**Hard:**
- GPU acceleration with CUDA
- American options (LSM)
- Multi-asset options
- Build pricing library

## Resources to Share

**When they want deeper theory:**
- Hull's book (industry standard)
- Glasserman's book (Monte Carlo focus)
- Wilmott's book (intuitive explanations)

**When they want more C++:**
- CppReference.com
- Effective Modern C++ (book)
- CppCon talks on YouTube

**When they want more finance:**
- QuantLib (open source library)
- QuantStart (tutorials)
- Coursera: Computational Finance

## Success Metrics

Your mentoring is successful if they:
1. **Understand** the concepts, not just the code
2. **Can explain** to others what they built
3. **Debug** their own issues
4. **Extend** the project independently
5. **Appreciate** both the math and the engineering

## Final Tips

**Be patient**: This combines finance, math, and C++ - it's a lot!

**Be encouraging**: Celebrate small wins, every working component is progress.

**Be curious**: Ask them questions, make them think.

**Be practical**: Connect to real-world applications.

**Be honest**: If you don't know something, look it up together.

---

Remember: The goal isn't just a working pricer, it's a deep understanding of Monte Carlo methods, options pricing, and high-performance C++. Take your time, ensure understanding at each step, and make it fun!
