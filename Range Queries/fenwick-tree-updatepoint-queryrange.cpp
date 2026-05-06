class Fenwick {
    int n;
    vector<ll> t;

    ll p(int i) {
        ll ret = 0;
        for (; i>0; i -= i&-i) ret += t[i];
        return ret;
    }

public:
    Fenwick(int _n):n(_n) { t.assign(n+1,0LL); }

    ll query(int l, int r) { return p(r) - p(l-1); }

    void update(int i, ll x) { // add x to a[i]
        if (i < 1) return;
        for (; i<=n; i += i&-i) t[i] += x;
    }

};