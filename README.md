# CP-References

Team reference notebook for ECPC. Every file has a header comment explaining the
theory, usage, complexity, pitfalls, and **CHANGE HERE** markers for the
per-problem parts (merge functions, alphabet, block sizes, ...).

**Template assumptions:** snippets rely on the usual macros being defined in the
main template — `ll`, `pb` (push_back), `sz(x)`, `all(x)`, `N` (array bound),
`mod`, `INF` — and won't compile standalone. Some files are full classes, some
are snippets meant to be pasted inside `solve()`.

**[NOTES.md](NOTES.md)** — one-line contest facts (number theory, bit identities, parity
arguments) plus a **Tricks** section: "see X → reach for Y" recipes and the
constraints→complexity map. Skim it before the contest and whenever a problem feels stuck.

## Index — what to grab when

### Range Queries
| File | Use when |
|---|---|
| `fenwick-tree-updatepoint-queryrange` | point `+=`, range **sum** — smallest/fastest option (1-indexed!) |
| `fenwick-tree-updaterange-querypoint` | range `+=`, read single element (difference trick, 1-indexed!) |
| `seg-tree` | point update, range **any merge** (min/max/gcd/custom struct) |
| `seg-tree-iterative` | same as above, faster constant, any n, memory 2n |
| `lazy-seg-tree` | **range** update + range query; variants (add/assign × sum/min) in header |
| `sparse-table` | **no updates**, O(1) min/max/gcd queries (idempotent ops only!) |
| `mo` | offline range queries, answer maintainable by moving endpoints ±1 |
| `mo-on-tree` | same but queries are **paths in a tree** (Euler-tour flattening) |
| `mo-with-rollback` | Mo when **delete is impossible** (running max, DSU, ...) — skeleton |
| `sqrt-decomposition` | block decomposition — when the per-block info is too weird for a segtree |

### Graph & Trees
| File | Use when |
|---|---|
| `dijkstra` | shortest paths, **non-negative** weights (multi-source / 0-1 BFS notes inside) |
| `bellman-ford` | shortest paths with **negative** edges + negative-cycle detection |
| `floyd-warshall` | **all-pairs** shortest paths, n ≤ ~500; transitive closure |
| `topological-sort` | order a DAG / detect cycle / DAG DP (Kahn) |
| `max-flow-dinic` | max flow, min cut, **bipartite matching** (recipes in header) |
| `dsu` | connectivity under edge additions, Kruskal, components |
| `lca` | LCA / k-th ancestor / tree distance (binary lifting) |
| `scc` | directed graph → SCCs + condensation DAG (comps come sinks-first → DP-ready) |
| `2-sat` | boolean vars with pairwise constraints (a∨b, forces, at-most-one) |
| `bridges-using-tarjan` | mark edges whose removal disconnects (handles parallel edges) |
| `articulation-points` | mark **vertices** whose removal disconnects (`low[v] >= in[u]` + root rule) |
| `bridge-tree` | shrink 2-edge-connected comps → tree; bridge/connectivity path problems |
| `hld` | path queries u→v with a segtree on top; edge-cost variant inside; free subtree ranges |

### Number Theory / Combinatorics
| File | Use when |
|---|---|
| `sieve` | primality table up to ~1e7 (see header: primes list caveat) |
| `linear-sieve` | smallest-prime-factor table → factorize many numbers in O(log) |
| `miller-rabin` | is THIS huge number (up to 2^64) prime — deterministic |
| `ext-gcd-crt` | inverse mod **non-prime** m, ax+by=c, linear congruences, CRT merge |
| `euler-phi` | totient (single + sieve); huge-exponent reduction a^b mod m |
| `divisors` | count + sum of divisors from factorization, O(√n) |
| `combinatorics` | nCr/nPr O(1) after O(n) precompute — **needs prime mod** |
| `ncr-pascal` | nCr when mod is NOT prime (O(N²), N ≤ ~4000) |
| `euler-pentagonal-partitions` | partition count p(n) in O(n√n) |

### Strings
| File | Use when |
|---|---|
| `hashing` | compare substrings O(1), LCP by binary search, palindromes (double hash) |
| `kmp` | pattern matching, borders, smallest period (prefix function) |
| `z-function` | "how far does s match itself from i" — matching, periods |
| `manacher` | ALL palindromes in O(n); O(1) "is s[l..r] a palindrome" |
| `multiset-hashing` | "same elements regardless of order" — anagram ranges, bag equality |
| `trie` | word/prefix dictionary with counts + delete |
| `binary-trie` | XOR problems: max XOR pair/subarray, online best-xor queries |

### Geometry
| File | Use when |
|---|---|
| `geometry-basics` | cross/orientation, segment intersection, polygon area, point-in-polygon |
| `convex-hull` | monotone chain (CCW) + farthest pair via rotating calipers |
| `closest-pair` | closest pair of points, O(n log n) sweep |

### DP
| File | Use when |
|---|---|
| `lis` | longest increasing subsequence O(n log n) + reconstruction (strict/non-strict switch) |
| `digit-dp` | count numbers in [L, R] with a digit property (worked example: sum % K) |
| `matrix-exponentiation` | linear recurrence / path counting with n up to 1e18 |
| `tree-knapsack` | "pick k vertices forming a connected piece of the subtree" DP, O(n²) |

### Other
| File | Use when |
|---|---|
| `coordinate-compression` | values 1e9+ needed as array indices |
| `ordered-multiset` | k-th smallest & count-less-than in O(log n) (pb_ds; read the erase warning!) |
| `random` | the rng; shuffle; random hash bases; stress tests |
| `bit-tricks` | count numbers in [l,r] with bit b set; XOR of 1..n in O(1) |

## Still missing (add only if the team wants them)
Suffix array / automaton, Aho-Corasick, FFT/NTT, min-cost max-flow,
convex hull trick / Li Chao, centroid decomposition, persistent structures.
