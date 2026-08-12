/*
 * FENWICK / BIT — point update, range SUM query.  O(log n) each, tiny constant.
 * -----------------------------------------------------------------------------
 * !! 1-INDEXED !!  Valid positions are 1..n. Index 0 breaks the loops (i&-i).
 *
 * USAGE:
 *   Fenwick f(n);
 *   f.update(i, x);     // a[i] += x   (to SET a[i]=v: update(i, v - current))
 *   f.query(l, r);      // sum of a[l..r]
 *
 * RECALL — why it works: t[i] stores the sum of the block of length (i & -i)
 * ending at i. Prefix sum p(i) walks i -> i - (i&-i) (strip lowest bit);
 * update walks the other way. Range sum = p(r) - p(l-1).
 *
 * WHEN Fenwick vs segtree: Fenwick only needs an INVERTIBLE op (sum, xor, count).
 *   min/max range queries -> use segtree/sparse table instead.
 *   XOR variant: replace both `+=` with `^=` and the `-` in query with `^` — done.
 *
 * CLASSIC TRICKS:
 *   - Count inversions: sweep the array, query how many seen values are > a[i].
 *   - "k-th smallest present value": Fenwick over values + binary lifting descent.
 *   - Values up to 1e9? coordinate-compress first (Other/coordinate-compression.cpp).
 *
 * Range UPDATE + point query -> see the sibling file (difference-array Fenwick).
 * Range update + range query -> needs 2 Fenwicks or a lazy segtree.
 */
class Fenwick {
    int n;
    vector<ll> t;

    ll p(int i) {                       // prefix sum a[1..i]
        ll ret = 0;
        for (; i>0; i -= i&-i) ret += t[i];
        return ret;
    }

public:
    Fenwick(int _n):n(_n) { t.assign(n+1,0LL); }

    ll query(int l, int r) { return p(r) - p(l-1); }

    void update(int i, ll x) { // add x to a[i]
        if (i < 1) return;              // guard: i=0 has i&-i == 0 -> would loop forever
        for (; i<=n; i += i&-i) t[i] += x;
    }

};
