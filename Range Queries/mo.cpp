/*
 * MO'S ALGORITHM — OFFLINE range queries in O((n + q) * sqrt(n) * cost(add/del))
 * ------------------------------------------------------------------------------
 * Use when: no updates, all queries known upfront, and the answer for [l, r]
 * can be MAINTAINED while moving the endpoints one step at a time.
 * Classics: # distinct values in range, # pairs, mode-ish counts, XXX-frequency stuff.
 *
 * RECALL — why it's fast:
 *   Sort queries by (block of l, then r). Inside one block R only sweeps ~n total
 *   (amortized), and L jiggles within a block of size SQ per query.
 *   The `(l/SQ)&1 ? r>... : r<...` is the SNAKE/parity order: alternate R's sweep
 *   direction per block -> R doesn't reset to the left each block (~2x speedup).
 *
 * SETUP — needs `const int SQ` defined:
 *   SQ ~ sqrt(n) (450 for n=2e5), or tuned:  SQ = max(1, n / max(1, (int)sqrt(q))).
 *
 * !! INDEXING: this template starts L=1, R=0 (empty window) -> queries are
 *    1-INDEXED inclusive. Keep your array 1-indexed to match.
 *
 * FILL IN (the whole problem lives in these three lambdas):
 *   add(i)    — element a[i] enters the window  (e.g. if (++cnt[a[i]] == 1) distinct++;)
 *   del(i)    — element a[i] leaves the window  (e.g. if (--cnt[a[i]] == 0) distinct--;)
 *   answer()  — current window's answer
 * Values up to 1e9 -> coordinate-compress first so cnt[] can be an array.
 *
 * ORDER MATTERS below: expand (add) BEFORE shrink (del) so the window never
 * goes "inside out" (L > R+1) — with e.g. cnt[]-- on absent elements that corrupts state.
 *
 * If delete is impossible/hard (max-so-far, DSU...) -> mo-with-rollback.cpp.
 * Path queries on a tree -> mo-on-tree.cpp.
 */
struct Query
{
    int l, r, idx;                    // idx = original position (answers go back in order)
    bool operator<(const Query& other) const {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;   // primary: block of l
        return ((l/SQ) & 1) ? r > other.r : r < other.r;    // snake order on r
    }
};

void MO(vector<Query>& queries, vector<int>& ans)
{
    sort(queries.begin(), queries.end());

    auto add = [&](int i) {
        // a[i] enters the window
    };

    auto del = [&](int i) {
        // a[i] leaves the window
    };

    auto answer = [&]() {
        return 0;                     // current window answer
    };

    int L = 1, R = 0;                 // empty window
    for (auto [l, r, idx] : queries) {
        while (l < L) add(--L);       // expand left
        while (R < r) add(++R);       // expand right
        while (L < l) del(L++);       // shrink left
        while (r < R) del(R--);       // shrink right

        ans[idx] = answer();
    }
}
