namespace dsu
{
    int sz; vector<int> p, len;

    void init(int n)
    {
        sz = n+1;
        p.resize(sz); len.resize(sz, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int v) {
        if (p[v] == v) return v;
        return p[v] = find(p[v]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (len[v] > len[u]) swap(u, v);
        p[u] = v;
        len[v] += len[u];
    }

    bool sameGroup(int u, int v) {
        return find(u) == find(v);
    }
}
using namespace dsu;