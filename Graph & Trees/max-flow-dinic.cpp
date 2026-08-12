/*
 * DINIC'S MAX FLOW — O(V^2 * E) general, O(E * sqrt(V)) on unit capacities
 * ------------------------------------------------------------------------
 * In practice miles faster than the bounds; handles n,m in the 1e4-1e5 range easily.
 *
 * USAGE:
 *   Dinic din(n);
 *   din.addEdge(u, v, cap);        // DIRECTED. For an UNDIRECTED edge use addEdge(u,v,c)
 *                                  // twice (both directions) or set back cap = c below.
 *   ll f = din.maxflow(s, t);
 *
 * RECALL — how it works: repeat { BFS from s on the RESIDUAL graph to build
 * levels; DFS pushing flow only along level+1 edges (blocking flow) }. The `it[]`
 * pointers make each edge scanned once per phase; <= V phases total.
 * Residual trick: pushing f on edge id also adds f capacity to id^1 (its reverse
 * twin — they're created together, that's why ids pair up as 2k / 2k+1).
 *
 * ===== RECIPES (what flow problems look like in contests) =====
 * BIPARTITE MATCHING (max # of disjoint pairs):
 *   source S -> every left node (cap 1), every right node -> sink T (cap 1),
 *   left u -> right v (cap 1) for each allowed pair. maxflow(S, T) = matching size.
 *   READ the matching: for each left->right edge with e[id].cap == 0 -> pair used.
 *   (Konig: min vertex cover = max matching; max independent set = V - matching.)
 * MIN CUT (= max flow value, Menger etc.):
 *   after maxflow, BFS from s using only edges with cap > 0; visited set = S-side.
 *   Cut edges = original edges from visited u to unvisited v.
 * NODE capacities / "each node used once": split node x into x_in -> x_out (cap = node cap).
 * MULTIPLE sources/sinks: super-source -> each source (cap INF), similarly sinks.
 */
struct Dinic {
    struct Edge { int to; ll cap; };
    int n;
    vector<Edge> e;                  // edges come in pairs: id and id^1 (the reverse)
    vector<vector<int>> g;           // g[u] = ids of edges out of u
    vector<int> level, it;

    Dinic(int n): n(n), g(n), level(n), it(n) {}

    void addEdge(int u, int v, ll cap) {
        g[u].pb(sz(e)); e.pb({v, cap});
        g[v].pb(sz(e)); e.pb({u, 0});    // reverse edge, cap 0 (put `cap` here for undirected)
    }

    bool bfs(int s, int t) {             // level graph on residual edges
        level.assign(n, -1);
        queue<int> q; q.push(s); level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u])
                if (e[id].cap > 0 && level[e[id].to] == -1) {
                    level[e[id].to] = level[u] + 1;
                    q.push(e[id].to);
                }
        }
        return level[t] != -1;           // t unreachable -> done, no more flow
    }

    ll dfs(int u, int t, ll pushed) {    // push a blocking flow along level+1 edges
        if (u == t || !pushed) return pushed;
        for (int& i = it[u]; i < sz(g[u]); i++) {   // it[u] persists: dead edges skipped forever
            int id = g[u][i], v = e[id].to;
            if (level[v] != level[u] + 1 || e[id].cap <= 0) continue;
            ll got = dfs(v, t, min(pushed, e[id].cap));
            if (got) {
                e[id].cap -= got;
                e[id^1].cap += got;      // give it back to the reverse edge (residual!)
                return got;
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            it.assign(n, 0);
            while (ll pushed = dfs(s, t, LLONG_MAX))
                flow += pushed;
        }
        return flow;
    }
};
