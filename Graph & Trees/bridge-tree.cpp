/*
 * BRIDGE TREE (a.k.a. 2-edge-connected component tree), O(n + m)
 * --------------------------------------------------------------
 * PIPELINE (3 steps below):
 *   1) Mark all bridges (Tarjan — see bridges-using-tarjan.cpp for the theory).
 *   2) Flood-fill WITHOUT crossing bridges -> comp[u] = 2-edge-connected component id.
 *      (inside a component, every pair of nodes has 2 edge-disjoint paths)
 *   3) Every bridge connects two different components -> those are the TREE edges.
 *
 * RESULT: `tree` = the bridge tree on `id` nodes. Any cycle of the original graph
 * is squeezed inside a single tree node, and every original bridge = a tree edge.
 *
 * WHY YOU WANT IT — turns "edge-connectivity" problems into TREE problems:
 *   - # bridges on the path u->v  =  tree-distance(comp[u], comp[v])
 *   - min edges to add to make the whole graph 2-edge-connected = (leaves + 1) / 2
 *   - "does removing edge e disconnect u from v" -> is e a bridge on their tree path
 *
 * SNIPPET (inside main). Nodes 1-indexed in input, converted to 0-indexed here.
 * Parallel edges are fine (parent skipped by edge id `pe`, not by node).
 */
int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);   // {v, edge id}
    vector<pair<int,int>> edges(m);
    for (int i=0; i<m; i++) {
        int u, v; cin >> u >> v;
        adj[--u].emplace_back(--v,i);
        adj[v].emplace_back(u,i);
        edges[i] = {u,v};
    }

    // -------- step 1: mark bridges --------
    int timer = 0;
    vector<bool> isBridge(m);
    vector<int> in(n,-1), low(n);           // in = -1 means unvisited
    function<void(int,int)> tarjan = [&](int u, int pe) {
        in[u] = low[u] = timer++;
        for (const auto& [v, e] : adj[u]) if (e != pe) {
            if (~in[v])
                low[u] = min(low[u], in[v]);        // back edge
            else {
                tarjan(v, e);
                low[u] = min(low[u], low[v]);
                if (low[v] > in[u]) isBridge[e] = true;
            }
        }
    };
    tarjan(0,-1);   // if the graph may be disconnected: loop over all unvisited nodes

    // -------- step 2: components = flood fill that never crosses a bridge --------
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

    // -------- step 3: bridges become the tree edges --------
    vector<vector<int>> tree(id);
    for (const auto& [u, v] : edges) {
        int cu = comp[u], cv = comp[v];
        if (cu != cv) {          // endpoints in different comps <=> this edge is a bridge
            tree[cu].pb(cv);
            tree[cv].pb(cu);
        }
    }
    // now run LCA / DFS / DP on `tree`; map original node u -> tree node comp[u]
