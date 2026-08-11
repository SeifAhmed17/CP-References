struct Query {
    int l, r, iq, lca;
    bool operator<(const Query& other) const {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return ((l/SQ)&1) ? r > other.r : r < other.r;
    }
};

void solve()
{
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin >> a[i], --a[i];
    vector<vector<int>> adj(n);
    for (int i=0; i<n-1; i++) {
        int u, v; cin >> u >> v;
        adj[--u].pb(--v);
        adj[v].pb(u);
    }

    int timer = 0;
    vector<int> in(n), out(n), lvl(n), flat(2*n), node(2*n);
    vector<vector<int>> anc(LOG, vector<int>(n));
    function<void(int,int)> dfs0 = [&](int u, int p) {
        in[u] = timer;
        node[timer++] = u;
        for (int v : adj[u]) if (v != p) {
            lvl[v] = lvl[u] + 1;

            anc[0][v] = u;
            for (int i=1; i<LOG; i++)
                anc[i][v] = anc[i-1][anc[i-1][v]];

            dfs0(v, u);
        }

        out[u] = timer;
        node[timer++] = u;
    };
    dfs0(0, -1);

    for (int i=0; i<n; i++) flat[in[i]] = flat[out[i]] = a[i];

    auto kth_ancestor = [&](int k, int u) {
        for (int i=0; i<LOG; i++) if (k>>i&1) u = anc[i][u];
        return u;
    };

    auto get_lca = [&](int u, int v) {
        if (lvl[u] > lvl[v]) swap(u, v);
        v = kth_ancestor(lvl[v]-lvl[u], v);
        if (u == v) return u;
        for (int i=LOG-1; i>=0; i--)
            if (anc[i][u] != anc[i][v])
                u = anc[i][u], v = anc[i][v];
        return anc[0][u];
    };

    vector<Query> queries(q);
    for (int i=0; i<q; i++) {
        int u, v; cin >> u >> v, --u, --v;
        if (lvl[u] > lvl[v]) swap(u, v);
        int lca = get_lca(u, v);
        if (lca == u) {
            queries[i] = {in[u], in[v], i, -1};
        }
        else {
            queries[i] = {out[u], in[v], i, lca};
        }
    }
    sort(all(queries));


    vector<int> answer(q), freqNode(n);

    auto add = [&](int i) {
        int x = flat[i]; 
        // x is the value itself
    };

    auto del = [&](int i) {
        int x = flat[i];
        // x is the value itself
    };

    auto process = [&](int i) {
        int u = node[i];
        if (++freqNode[u] & 1) add(in[u]);
        else del(in[u]);
    };

    auto get_answer = [&] {
        return 0; // placeholder
    };

    int L = 0, R = -1;
    for (const auto& [l, r, iq, lca] : queries) {
        while (l < L) process(--L);
        while (R < r) process(++R);
        while (L < l) process(L++);
        while (r < R) process(R--);
        if (~lca) add(in[lca]);
        answer[iq] = get_answer();
        if (~lca) del(in[lca]);
    }

    for (int x : answer) cout << x << '\n';
}