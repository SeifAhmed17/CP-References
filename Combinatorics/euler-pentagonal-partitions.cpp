/*
 * PARTITION FUNCTION p(n) — Euler's Pentagonal Number Theorem
 * -----------------------------------------------------------
 * p(n) = number of ways to write n as a sum of positive integers, ORDER DOESN'T MATTER.
 *   e.g. p(4) = 5:  4, 3+1, 2+2, 2+1+1, 1+1+1+1
 *
 * RECURRENCE (this is the whole theorem):
 *   p(n) = sum over k=1,2,3,...  of  (-1)^(k-1) * [ p(n - g1(k)) + p(n - g2(k)) ]
 *   where g1(k) = k(3k-1)/2 and g2(k) = k(3k+1)/2  (generalized pentagonal numbers:
 *   1, 2, 5, 7, 12, 15, 22, 26, ...). Stop when g1(k) > n.
 *   Signs alternate in PAIRS: +, +, -, -, +, +, ...  (that's the k&1 check below)
 *
 * COMPLEXITY: O(n * sqrt(n)) — only O(sqrt n) pentagonal numbers are <= n.
 *   n = 1e5 -> ~3e7 ops, fine.
 *
 * This is a SNIPPET (goes inside main/solve). Needs: n, mod.
 * Base case p(0) = 1 (the empty sum).
 */
vector<ll> p(n+1);
p[0] = 1;
for (int i=1; i<=n; i++) {
    for (int k=1; ; k++) {
        ll g1 = 1LL * k * (3 * k - 1) / 2;   // pentagonal number
        ll g2 = 1LL * k * (3 * k + 1) / 2;   // its pair

        if (g1 > i) break;                   // both too big -> done with i

        ll term = p[i - g1];
        if (g2 <= i) term = (term + p[i - g2]) % mod;

        if (k & 1) p[i] = (p[i] + term) % mod;        // odd k  -> add
        else p[i] = (p[i] - term + mod) % mod;        // even k -> subtract
    }
}
