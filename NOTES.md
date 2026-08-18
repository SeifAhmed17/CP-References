# Contest Notes

Quick facts that solve or unlock problems. (Code lives in the folders; see README index.)

## Setup & don't-forget

- **Fast IO** — first lines of main: `ios_base::sync_with_stdio(false); cin.tie(nullptr);` — after this NEVER mix in `scanf`/`printf`.
- `'\n'` not `endl` (endl flushes = slow in loops). **Exception: interactive problems** — there you MUST flush every query (`endl` or `cout.flush()`).
- **Interactive protocol**: `cout << "? " << x << endl;` then read the reply — `endl` everywhere, no buffering games. Note `cin.tie(nullptr)` disables the auto-flush-before-read, so with fast IO every un-flushed query = guaranteed idleness TLE.
- If the judge replies `-1` (or anything out of protocol) → `exit(0)` **immediately**: you exceeded the query budget or sent garbage, and looping on turns a clean WA into a confusing TLE.
- Finish with `! answer` + flush; count queries against the budget first (it's usually ~log₂n — an off-by-one loop bound is the classic interactive WA).
- Multi-test skeleton: `int t; cin >> t; while (t--) solve();` — **reset globals/arrays inside solve()**, half of all WAs on test 2 are stale state.
- Real-number answers: `cout << fixed << setprecision(10);` — default prints 6 significant digits and truncates big values into scientific notation.
- Overflow: `1e5 * 1e5` overflows int **silently** — cast first: `(ll)a * b`. Shifts: `1LL << k`, not `1 << k`, for k ≥ 31. Constants: `const ll INF = 4e18;` (int max ~2.1e9).
- Big arrays **global**, never inside main — local ones overflow the stack. Same for recursion deeper than ~1e5 on some judges.
- `v.size()` is unsigned: `v.size() - 1` on an empty vector = huge number — write `(int)v.size()`.
- `sort` comparator must be **strict** (`<`, never `<=`) — a non-strict one is undefined behavior (can RE, not just missort).
- Read until EOF: `while (cin >> x) { ... }`. File IO when the judge wants it: `freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);`
- Compile: `g++ -O2 -std=c++17 a.cpp -o a` — while debugging add `-g -fsanitize=address,undefined` (catches overflow, out-of-bounds, UB at runtime).

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

## Games (Grundy)

- Grundy number of a position = **mex of the Grundy numbers of positions reachable in one move**. Position is LOSING for the player to move **iff g = 0**. Compute by memoized DFS over the game graph.
- **Sum of independent games** (each turn: move in exactly ONE component): total g = **XOR of the components' g** — losing iff the XOR is 0. This is why single-game Grundy tables solve multi-pile problems.
- **Nim** (take any amount from one pile): g(pile of n) = n → first player wins iff XOR of piles ≠ 0. Winning move: pick a pile where `p ^ total < p`, shrink it to `p ^ total`.
- Subtraction game (take 1..k): **g(n) = n mod (k+1)**. Unknown small game? **Brute-force g(n) for n ≤ 60 and look for the period** — most simple games are eventually periodic.
- **Misère nim** (who takes last LOSES): play exactly like normal nim, EXCEPT when every pile has size 1 — then first wins iff the number of piles is **even**.
- **Staircase nim** (move stones one step down a staircase): only stones on **odd steps** matter — XOR those pile sizes.
- No Grundy needed if you can find a **mirroring/pairing strategy**: copy the opponent's move in the symmetric half — proves a win without any computation. Also try "strategy stealing" for existence proofs.

## Expected value

- **Linearity of expectation**: E[X+Y] = E[X] + E[Y] — **works even when dependent**. The main move: write the target as a sum of 0/1 indicators, then E[total] = Σ P(indicator = 1). ("Expected # of visible towers / inversions / adjacent equal pairs...")
- Nonnegative integer X: **E[X] = Σ P(X ≥ k), k = 1, 2, ...** — often much easier than finding the full distribution ("expected number of rounds survived").
- Waiting times: success probability p → expected tries = **1/p**. **Coupon collector**: expected draws to see all n types = n·(1 + 1/2 + ... + 1/n) ≈ n ln n.
- k independent uniform [0,1]: **E[min] = 1/(k+1), E[max] = k/(k+1)**, i-th smallest = i/(k+1). Same fractions for "k random cuts of a stick".
- Random permutation of n: expected **fixed points = 1** (any n!), expected **# cycles = 1 + 1/2 + ... + 1/n**, P(two given elements share a cycle) = **1/2**.
- Random process with states → set unknowns E[state] = expected steps to finish, write one linear equation per state, solve: telescoping for chains/lines, **Gaussian elimination** for ≤ a few hundred states.
- **Gambler's ruin** (fair ±1 walk from i, absorbing at 0 and n): P(reach n first) = **i/n**; expected steps = **i·(n−i)**.

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
- Same flip for **subsets**: each element lies in **2^(n−1)** of the 2^n subsets → sum of sizes over all subsets = **n·2^(n−1)**; each PAIR lies in 2^(n−2) (Σ over subsets of #pairs = C(n,2)·2^(n−2)), and so on — "sum of f over all subsets" usually collapses to one closed form per element/pair.
- "Count pairs (i, j) with condition" → sort + two pointers, or sweep left→right holding earlier elements in a Fenwick over values (inversions pattern).
- Answer is min/max cost with weird operations → hunt for an **invariant** first (sum mod k, parity, coloring) — it gives impossibility proofs AND constructions.
- Operations look irreversible → **reverse the process** (deletions become insertions, run queries backwards, last move first).
- Optimize over sequences with an exchangeable order → **sort by an exchange argument**: comparator "a before b iff ab-combined beats ba-combined" (classic: concatenate numbers into the largest string).

### Arrays & queries

- Range ADD, values read only at the end → **difference array**: `d[l] += x, d[r+1] −= x`, prefix at the end. 2D: ±x at the 4 corners, 2D prefix.
- "Max number of overlapping intervals" → **events**: +1 at l, −1 at r+1, running maximum of the prefix sum.
- "Sum of max (or max−min) over ALL subarrays" → per-element: a[i] is the max of **(i−L)·(R−i)** subarrays, L/R = nearest greater neighbors via monotonic stack, O(n). **Duplicates**: strict compare on one side, ≥ on the other — else equal maxima get counted twice/zero times. Do max and min in separate passes, subtract.
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
