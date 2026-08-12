/*
 * TREE KNAPSACK / "merging subtree DPs" — O(n^2) total (NOT n^3!)
 * ---------------------------------------------------------------
 * dp[u][k] = best total value of a CONNECTED subgraph that contains u,
 *            stays inside u's subtree, and has exactly k vertices.
 * (connected + contains u  <=>  "u plus some children subtree-pieces")
 *
 * RECALL — the merge (it's just 0/1 knapsack over children):
 *   process child v: dp[u][i + j] <- dp[u][i] + dp[v][j]
 *   - i loops DOWNWARD over what u had BEFORE this child -> each child used once
 *     (same reason 0/1 knapsack loops capacity downward)
 *   - loops are capped by size[u]-so-far and size[v]; that cap is the whole magic:
 *     each PAIR of vertices (x in earlier part, y in v) is counted once, at their LCA
 *     -> total work = #pairs = O(n^2). NEVER loop to n — that makes it O(n^3).
 *
 * SNIPPET (inside solve). Needs: n, adj, a (node values), INF (~1e18 with ll dp).
 * -INF marks "impossible size". Answer: max over dp[0][k] (root=0) for the k you need;
 * for "best anywhere in the tree", also consider dp[u][k] at every u — any connected
 * subgraph is captured at its TOPMOST node.
 *
 * VARIANTS with the same skeleton: "keep k edges/vertices, maximize", counting
 * versions (sum instead of max, mod), costs on edges (add edge cost when j > 0).
 */
vector<vector<ll>> dp(n, vector<ll>(n+1, -INF));
    vector<int> size(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        dp[u][1] = a[u];                        // just u itself
        size[u] = 1;
        for (int v : adj[u]) if (v != p) {
            dfs(v, u);

            // knapsack-merge v into u; i DOWNWARD, both loops size-capped (see header)
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
