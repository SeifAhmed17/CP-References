vector<int> adj[N];
int in[N], low[N], timer=1;
vector<pair<int,int>> bridges;

void dfs(int u, int p) {
    in[u] = low[u] = timer++;
    for (int v : adj[u]) if (v != p) {
        if (!in[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > in[u])
                bridges.emplace_back(u, v);
        }
        else low[u] = min(low[u], in[v]);
    }
}