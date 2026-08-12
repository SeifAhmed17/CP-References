/*
 * SPARSE TABLE — STATIC array, O(n log n) build, O(1) range query
 * ---------------------------------------------------------------
 * No updates allowed! If you need updates -> segment tree.
 *
 * USAGE:  SparseTable st(a);  st.query(l, r);   // 0-indexed, inclusive
 *
 * RECALL — how it works:
 *   t[k][i] = merge of the 2^k elements starting at i.
 *   Query [l..r]: take the two 2^k blocks covering the range from each end —
 *   they OVERLAP in the middle, which is why the op must be IDEMPOTENT:
 *
 *   >>> merge must satisfy f(x, x) = x:  min / max / gcd / AND / OR  — YES
 *   >>> sum / xor / count               — NO! (overlap counts twice)
 *       for sums use prefix sums; or query the disjoint O(log n) way.
 *
 * CHANGE HERE: `merge` (currently min).
 *
 * __lg(x) = floor(log2(x)) (GCC builtin). Build memory: O(n log n) ints.
 */
class SparseTable {

    private:
        vector<vector<int>> t;
        int n, LOG;
        int merge(int e, int o) { return min(e, o); }   // CHANGE: min/max/gcd/AND/OR only!

    public:

        SparseTable(vector<int>& a) {
            n = a.size(), LOG = 32 - __builtin_clz(n);  // = floor(log2(n)) + 1
            t.resize(LOG, vector<int>(n));

            for (int i=0; i<n; i++) t[0][i] = a[i];     // level 0 = the array itself

            for (int k=1; (1<<k)<=n; k++) {
                for (int i=0; i+(1<<k)<=n; i++) {
                    // block of 2^k = two adjacent blocks of 2^(k-1)
                    t[k][i] = merge(t[k-1][i], t[k-1][i+(1<<(k-1))]);
                }
            }
        }

        int query(int l, int r) {           // 0-indexed inclusive, needs l <= r
            int k = __lg(r-l+1);
            return merge(t[k][l], t[k][r-(1<<k)+1]);   // two overlapping blocks
        }
    };
