class Fenwick {
    int n;
    vector<ll> t;
    void u(int i, ll x) { // point-update the underlying diff-array Fenwick
        for (; i<=n; i += i&-i) t[i] += x;
    }
public:
    Fenwick(int _n):n(_n) { t.assign(n+1,0LL); }
    ll query(int i) { // returns a[i]
        ll ret = 0;
        for (; i>0; i -= i&-i) ret += t[i];
        return ret;
    }
    void update(int l, int r, ll x) { // add x to a[l..r]
        if (l > r || r < 1) return;
        if (l < 1) l = 1;
        u(l, x);
        if (r+1 <= n) u(r+1, -x);
    }
};