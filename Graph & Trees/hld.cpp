int n, timer, sz[N], in[N], tree[N], big[N], head[N], par[N], lvl[N];
vector<int> adj[N];

void dfs0(int u, int p) {
    sz[u] = 1;
    big[u] = -1;
    for (int v : adj[u]) if (v != p) {
        par[v] = u;
        lvl[v] = lvl[u]+1;
        dfs0(v, u);
        sz[u] += sz[v];
        if (big[u] == -1 || sz[v] > sz[big[u]]) big[u] = v;
    }
}

void decompose(int u, int p) {
    tree[timer] = u;
    in[u] = timer++;
    if (~big[u]) {
        head[big[u]] = head[u];
        decompose(big[u], u);
    }

    for (int v : adj[u]) if (v != p && v != big[u]) {
        head[v] = v;
        decompose(v, u);
    }
}

vector<pair<int,int>> getRanges(int u, int v) {
    vector<pair<int,int>> ranges;
    while (true) {
        if (head[u] == head[v]) {
            if (lvl[u] > lvl[v]) swap(u, v);
            ranges.emplace_back(in[u], in[v]);
            break;
        }

        if (lvl[head[u]] < lvl[head[v]]) swap(u, v);
        ranges.emplace_back(in[head[u]], in[u]);
        u = par[head[u]];
    }
    return ranges;
}