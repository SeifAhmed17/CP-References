/*
 * FENWICK / BIT — RANGE update, POINT query (difference-array trick). O(log n).
 * -----------------------------------------------------------------------------
 * !! 1-INDEXED !!  Valid positions are 1..n.
 *
 * USAGE:
 *   Fenwick f(n);
 *   f.update(l, r, x);   // a[i] += x  for ALL i in [l, r]
 *   f.query(i);          // current value of a[i]
 *
 * RECALL — the trick: keep Fenwick over the DIFFERENCE array d (d[i] = a[i]-a[i-1]).
 *   "add x on [l..r]"  =  d[l] += x, d[r+1] -= x        (two point updates)
 *   "value of a[i]"    =  prefix sum d[1..i]            (one prefix query)
 *
 * The array starts as all zeros. If you have initial values, either:
 *   - do update(i, i, a0[i]) for each i, or
 *   - just add a0[i] yourself when reading query(i).
 */
class Fenwick {
    int n;
    vector<ll> t;
    void u(int i, ll x) { // point-update the underlying diff-array Fenwick
        for (; i<=n; i += i&-i) t[i] += x;
    }
public:
    Fenwick(int _n):n(_n) { t.assign(n+1,0LL); }
    ll query(int i) { // returns a[i] = prefix sum of diffs
        ll ret = 0;
        for (; i>0; i -= i&-i) ret += t[i];
        return ret;
    }
    void update(int l, int r, ll x) { // add x to a[l..r]
        if (l > r || r < 1) return;
        if (l < 1) l = 1;             // clamp instead of crashing
        u(l, x);
        if (r+1 <= n) u(r+1, -x);     // r == n -> no cancel needed
    }
};
