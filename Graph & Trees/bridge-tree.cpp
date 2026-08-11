int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<pair<int,int>> edges(m);
    for (int i=0; i<m; i++) {
        int u, v; cin >> u >> v;
        adj[--u].emplace_back(--v,i);
        adj[v].emplace_back(u,i);
        edges[i] = {u,v};
    }

    int timer = 0;
    vector<bool> isBridge(m);
    vector<int> in(n,-1), low(n);
    function<void(int,int)> tarjan = [&](int u, int pe) {
        in[u] = low[u] = timer++;
        for (const auto& [v, e] : adj[u]) if (e != pe) {
            if (~in[v])
                low[u] = min(low[u], in[v]);

            else {
                tarjan(v, e);
                low[u] = min(low[u], low[v]);
                if (low[v] > in[u]) isBridge[e] = true;
            }
        }
    };
    tarjan(0,-1);


    vector<int> comp(n,-1); int id = 0;
    function<void(int)> setComp = [&](int u) {
        comp[u] = id;
        for (const auto& [v, e] : adj[u]) if (!isBridge[e] && comp[v] == -1) {
            setComp(v);
        }
    };
    for (int i=0; i<n; i++) {
        if (comp[i] == -1) {
            setComp(i);
            id++;
        }
    }

    vector<bool> cycle(id);
    vector<vector<int>> tree(id);
    for (const auto& [u, v] : edges) {
        int cu = comp[u], cv = comp[v];
        if (cu == cv); // not a bridge
        else { // bridge
            tree[cu].pb(cv);
            tree[cv].pb(cu);
        }
    }