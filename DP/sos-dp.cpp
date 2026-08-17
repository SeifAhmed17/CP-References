/*
 * SOS DP (sum over subsets) — f[m] = sum of a[s] over all submasks s of m
 * -----------------------------------------------------------------------
 * O(B * 2^B) for B bits — beats the naive 3^B submask loop when you need ALL masks.
 * Think of it as a B-dimensional prefix sum: one bit-dimension per pass.
 *
 * USAGE: load point values into f, run the loop, read answers from f (in-place).
 *
 * RECALL:
 *   - SUPERSET sums: flip the condition — add f[m | 1<<b] when bit b is NOT set.
 *   - Inverse (recover point values from submask sums / do exact-cover
 *     inclusion-exclusion): same loops, SUBTRACT instead of add.
 *   - "count pairs with a & b == 0": b must be a submask of ~a -> SOS over
 *     complements. "a & b == a" pairs -> superset sums.
 *   - Single mask only? enumerate its submasks directly in O(2^popcount):
 *       for (int s = m; s; s = (s - 1) & m) { ... use s ... }   // add s=0 if needed
 *     Over ALL m together that's the 3^B total — fine for B <= ~20 offline.
 *   - max/min instead of +: works the same (it's just a different monoid).
 */
namespace SOS
{
    int B;                 // number of bits, masks are 0 .. 2^B - 1
    vector<ll> f;          // in: f[mask] = point value; out: f[mask] = sum over submasks

    void sos() {
        for (int b = 0; b < B; b++)
            for (int m = 0; m < (1 << B); m++)
                if (m >> b & 1) f[m] += f[m ^ (1 << b)];
        // superset version: if (!(m >> b & 1)) f[m] += f[m | (1 << b)];
        // inverse: same loops, f[m] -= ...  (undoes one bit-dimension per pass)
    }
}
