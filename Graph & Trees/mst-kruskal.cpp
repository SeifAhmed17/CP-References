/*
 * MST — KRUSKAL, O(m log m)
 * -------------------------
 * Sort edges ascending, greedily take any edge whose endpoints are in
 * different components (DSU). Self-contained mini-DSU included below.
 *
 * USAGE:
 *   Kruskal::init(n); Kruskal::edges.push_back({w, u, v}); ...
 *   ll total = Kruskal::mst();     // -1 if graph is disconnected
 *   Kruskal::treeEdges             // the n-1 chosen {w, u, v} (build adj from it)
 *
 * RECALL — properties that solve problems (often no MST code needed at all):
 *   - CUT property: the lightest edge crossing ANY cut is in some MST.
 *   - MST minimizes the MAXIMUM edge over the path for EVERY pair u,v
 *     -> "minimize the max edge u->v" = sort edges + DSU, stop when u,v connect
 *        (no tree needed). All-pairs version: path-max on the MST via lca.cpp.
 *   - MAXIMUM spanning tree: sort descending.
 *   - Which edges can be in some MST? Process equal-weight GROUPS together:
 *     an edge is useless iff its endpoints were already connected BEFORE its group.
 *   - Second-best MST = min over non-tree edges (u,v,w) of  MST - maxEdgeOnPath(u,v) + w.
 */
namespace Kruskal
{
    int n; vector<int> par, len;
    vector<array<ll,3>> edges, treeEdges;          // {w, u, v}

    void init(int n_) {
        n = n_;
        par.assign(n+3, 0), len.assign(n+3, 1);
        iota(all(par), 0);
        edges.clear(), treeEdges.clear();
    }
    int find(int u) { return par[u] == u ? u : par[u] = find(par[u]); }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (len[u] < len[v]) swap(u, v);
        par[v] = u, len[u] += len[v];
        return true;
    }

    ll mst() {
        sort(all(edges));                          // by weight (first field)
        ll total = 0;
        for (auto& [w, u, v] : edges)
            if (merge(u, v)) total += w, treeEdges.push_back({w, u, v});
        // n-1 edges  <=>  connected; anything less means a forest
        return (int)treeEdges.size() == n - 1 ? total : -1;
    }
}
