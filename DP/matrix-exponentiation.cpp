/*
 * MATRIX EXPONENTIATION — linear recurrences in O(k^3 log b)
 * ----------------------------------------------------------
 * WHEN: f(n) depends linearly on the previous k terms and n is HUGE (1e18).
 *   f(n) = c1*f(n-1) + c2*f(n-2) + ... + ck*f(n-k)   ->   answer = T^n * base
 *
 * RECIPE (Fibonacci as the example, f(0)=0, f(1)=1):
 *   T = {{1,1},                      // [f(n+1)]   [1 1] [f(n)  ]
 *        {1,0}};                     // [f(n)  ] = [1 0] [f(n-1)]
 *   auto Tn = binPow(T, n);          // T^n
 *   f(n) = Tn[1][0]*f(1) + Tn[1][1]*f(0)  (or read off Tn[0][1] = f(n) directly for fib)
 * General k: first row = the coefficients c1..ck, subdiagonal = 1s (shift register).
 *
 * ALSO WORKS FOR: # of paths of length EXACTLY n in a graph (T = adjacency matrix!),
 * probabilities/expected values with fixed transitions, "DP with tiny state, giant n".
 *
 * !! PITFALL: binPow takes `a` BY REFERENCE and DESTROYS it (squares it in place).
 *    Pass a copy if you need the matrix again:  auto tmp = T; auto Tn = binPow(tmp, n);
 *
 * Feasibility: k^3 * log(n) -> k=100, n=1e18 is ~6e7 mults, OK.
 */
vector<vector<int>> mult(vector<vector<int>>& a, vector<vector<int>>& b) {
    const int n = a.size(), k = a[0].size(), m = b[0].size();   // (n x k) * (k x m)
    vector<vector<int>> ret(n, vector<int>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            for (int z=0; z<k; z++) {
                ret[i][j] = (ret[i][j] + 1LL * a[i][z] * b[z][j] % mod) % mod;
            }
        }
    }
    return ret;
}

vector<vector<int>> binPow(vector<vector<int>>& a, ll b) {   // !! modifies a (see header)
    const int n = a.size(), m = a[0].size();
    vector<vector<int>> ret(n, vector<int>(m));
    for (int i=0; i<n; i++) ret[i][i] = 1;      // identity matrix

    while (b) {
        if (b&1) ret = mult(ret, a);
        a = mult(a, a);
        b >>= 1;
    }

    return ret;
}
