namespace DSU
{
    int sz; vector<int> par, len;

    void init(int n)
    {
        sz = n+3;
        par.assign(sz, 0), len.assign(sz, 1);
        iota(all(par), 0);
    }

    int find(int u) {
        return par[u] == u ? u : par[u] = find(par[u]);
    }

    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (len[u] < len[v]) swap(u, v);
        par[v] = u, len[u] += len[v];
        return true;
    }
}
using namespace DSU;