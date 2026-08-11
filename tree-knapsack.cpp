vector<vector<ll>> dp(n, vector<ll>(n+1, -INF));
    vector<int> size(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        dp[u][1] = a[u];
        size[u] = 1;
        for (int v : adj[u]) if (v != p) {
            dfs(v, u);

            for (int i=size[u]; i ;i--) {
                for (int j=1; j<=size[v]; j++) {
                    if (dp[u][i] == -INF || dp[v][j] == -INF) continue;
                    dp[u][i+j] = max(dp[u][i+j], dp[u][i] + dp[v][j]);
                }
            }

            size[u] += size[v];
        }
    };
    dfs(0, -1);