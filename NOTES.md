# Contest Notes

Quick facts that solve or unlock problems. (Code lives in the folders; see README index.)

## Number theory

- The number of divisors of N is **odd iff N is a perfect square** (divisors pair up except √N). → `Number Theory/divisors.cpp`
- All common divisors of a, b are exactly the divisors of **gcd(a, b)**.
- Starting from 0 and repeatedly adding STEP mod MOD, you can reach **every** value 0..MOD-1 **iff gcd(STEP, MOD) = 1**.
- Every even number > 2 is a sum of two primes (Goldbach — a conjecture, but verified far past any contest limit).
- The largest gap between consecutive primes below 1e9 is only **~300** → "find a prime near x" loops terminate almost instantly.
- N is divisible by 6 iff N is even **and** its digit sum is divisible by 3.
- Euler's theorem: **a^φ(m) ≡ 1 (mod m)** when gcd(a, m) = 1.
- Huge exponents: **a^n ≡ a^(n mod φ(m) + φ(m)) (mod m)** for n ≥ log₂(m) — safe even when gcd(a, m) ≠ 1; drop the +φ(m) only if gcd = 1. → `Number Theory/euler-phi.cpp`

## Bits

- `n & (n-1)` — turn off the rightmost set bit (also: loop it to count set bits / test power of two).
- `n & (n+1)` — clear all trailing ones.
- `n | (n+1)` — set the rightmost zero bit.
- `n & -n` — extract the lowest set bit; note it always **divides n**.
- Number of set bits in [1, 2^k - 1] = **k · 2^(k-1)**.
- Count of numbers in [l, r] with a given bit set: O(1) per bit. → `Other/bit-tricks.cpp`
- Prefix XOR 1^2^...^n is periodic mod 4: **n, 1, n+1, 0** for n % 4 = 0, 1, 2, 3. → `Other/bit-tricks.cpp`
- N is a sum of K powers of two (repeats allowed) **iff popcount(N) ≤ K ≤ N**.

## Misc

- Chessboard N×M: number of white squares = **(N·M + fg) / 2** where fg = 1 if the corner square is white, else 0.
- A binary string with no palindromic substring of length > 1 has length ≤ 2 (adjacent chars must differ AND s[i] ≠ s[i+2] — contradiction from length 3 on).
- Any swap in a permutation changes the inversion count by an **odd** amount (flips parity). So 3-cycles preserve parity, and a duplicate value works as a "free parity reset" (swapping equal elements changes nothing).
- Minimum swaps to sort a permutation = n − (number of cycles in it).

## Tricks

"See X → reach for Y" recipes. Skim when a problem feels unapproachable.

### Picking the attack

- "**Minimize the maximum**" / "maximize the minimum" / "k-th smallest value" → **binary search on the answer**: write `possible(x)`, it's monotonic; for k-th smallest, count how many ≤ mid.
- "Count subarrays with sum/xor = k" → **prefix + hashmap**: `pre[r] − pre[l−1] = k` means look up `pre[r] − k` among earlier prefixes (xor: `pre[r] ^ k`).
- Window property **monotonic** (adding elements only hurts / only helps) → **two pointers** instead of binary search per position.
- "Sum of f over ALL subarrays/pairs" → flip to **per-element contribution**: a[i] sits in (i+1)·(n−i) subarrays; count how often each element/bit/pair is counted instead of iterating objects.
- "Count pairs (i, j) with condition" → sort + two pointers, or sweep left→right holding earlier elements in a Fenwick over values (inversions pattern).
- Answer is min/max cost with weird operations → hunt for an **invariant** first (sum mod k, parity, coloring) — it gives impossibility proofs AND constructions.
- Operations look irreversible → **reverse the process** (deletions become insertions, run queries backwards, last move first).
- Optimize over sequences with an exchangeable order → **sort by an exchange argument**: comparator "a before b iff ab-combined beats ba-combined" (classic: concatenate numbers into the largest string).

### Arrays & queries

- Range ADD, values read only at the end → **difference array**: `d[l] += x, d[r+1] −= x`, prefix at the end. 2D: ±x at the 4 corners, 2D prefix.
- "Max number of overlapping intervals" → **events**: +1 at l, −1 at r+1, running maximum of the prefix sum.
- **# distinct values in range** without Mo: offline, sort queries by r; sweep r with a Fenwick: +1 at position of value, −1 at its previous occurrence; answer = sum over [l, r].
- Online too hard? Almost every query problem collapses **offline**: sort queries by r / by value / by block and sweep. ("edges with weight ≤ X connect u,v?" → sort both, grow a DSU.)
- Frequencies + √ threshold: values occurring > √n times number ≤ √n ("heavy") — brute-force the heavy ones, bound the light ones per group.
- Divisor-style double loop `for d { for (j = d; j <= n; j += d) }` is **O(n log n)**, not O(n²) — harmonic series. Basis of many counting DPs.
- k-th smallest / rank queries on values up to 1e9 → coordinate-compress, Fenwick over ranks, or `ordered-multiset`.

### Graphs & trees

- **Subtree queries → Euler tour**: subtree(u) is the contiguous range [in[u], in[u]+sz[u]−1] — Fenwick/segtree on the tour order (the HLD ordering gives this for free).
- Path ADD on a tree, read at the end → **tree difference**: +x at u and v, −x at lca, −x at par[lca]; final value of a node = sum over its subtree (one DFS).
- "Remove edges" / "destroy nodes" queries → process **in reverse** with DSU: deletions become additions.
- "Nearest special cell/node" for every position → **multi-source BFS** (push all specials at distance 0).
- Edge weights only 0/1 → **0-1 BFS** with a deque (`push_front` on 0-edges) — Dijkstra without the log.
- Collecting sets up a tree (colors in subtree, ...) → **small-to-large**: always merge the smaller set into the bigger; total O(n log² n).
- "Answer for EVERY node as root" → **rerooting**: one DFS computing down-answers, a second pushing the parent-side answer down (combine prefix/suffix over children).
- Each node has exactly one outgoing edge (functional graph) → it's cycles with trees hanging off; k-th successor via binary lifting like `lca.cpp`.

### When stuck

- Write the **brute force anyway** (n ≤ 8): stare at outputs for the pattern, then keep it for stress testing against the real solution with `Other/random.cpp`.
- Fix something and see what's left: the maximum element, the leftmost chosen index, the root — "enumerate the boss, optimize the rest".
- Constraints are a hint (rough map):
  n ≤ 11 → O(n!) · n ≤ 20 → bitmask 2ⁿ · n ≤ 40 → meet in the middle ·
  n ≤ 500 → O(n³) · n ≤ 5000 → O(n²) · n ≤ 2·10⁵ → O(n log n) ·
  n ≤ 10⁶ → O(n) · n ~ 10⁹ → O(√n) / math · n ~ 10¹⁸ → O(log n): binary search / matrix expo / digit DP.
