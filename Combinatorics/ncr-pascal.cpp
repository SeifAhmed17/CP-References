/*
 * nCr VIA PASCAL'S TRIANGLE
 * -------------------------
 * c[n][r] = C(n, r) % mod, built with c[n][r] = c[n-1][r] + c[n-1][r-1].
 *
 * WHEN to prefer this over the factorial version (combinatorics.cpp):
 *   - mod is NOT prime (no modular inverse needed here!)
 *   - or you want plain (unmodded) values for small n (drop the % mod, use ll, n <= 66 fits ll)
 *
 * COST: O(N^2) time AND memory -> N up to ~3000-4000 max
 *       (ll c[N][N] with N=4000 is already ~128 MB; use int if mod < 2^31 to halve it).
 *
 * NOTES:
 *   - Entries with r > n stay 0 (globals are zero-initialized) -> safe to read.
 *   - Call pascal() once at startup.
 */
ll c[N][N];

void pascal()
{
    for (int i=0; i<N; i++) {
        c[i][0] = c[i][i] = 1;               // C(n,0) = C(n,n) = 1
        for (int j=1; j<i; j++) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod; // take or skip the last element
        }
    }
}
