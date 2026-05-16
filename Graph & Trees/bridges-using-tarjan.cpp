vector<pair<int,int>> adj[N];
int n, m, timer = 1, in[N], low[N], isBridge[N];

void tarjan(int u, int p) {
    in[u] = low[u] = timer++;
    for (const auto& [v, e] : adj[u]) if (v != p) {
        if (in[v])
            low[u] = min(low[u], in[v]);
        else {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > in[u])
                isBridge[e] = true;
        }
    }
}