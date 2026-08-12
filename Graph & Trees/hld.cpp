/*
 * HEAVY-LIGHT DECOMPOSITION (HLD)
 * -------------------------------
 * Answer PATH queries (sum/min/max on the path u..v) with a segment tree,
 * and support point/range updates. Each query touches O(log n) chains,
 * so total O(log^2 n) per query with a segtree on top.
 *
 * RECALL — the idea:
 *   - big[u] = "heavy child" = child with the largest subtree.
 *   - decompose() writes nodes in an order where every heavy chain is CONTIGUOUS,
 *     in[u] = position of node u in that order, head[u] = top node of u's chain.
 *   - Walking u -> root switches chains only O(log n) times, because every time
 *     you leave a chain top, the subtree size at least doubles.
 *
 * SETUP (order matters):
 *   1) build adj, choose root r (usually 0)
 *   2) dfs0(r, -1);                       // sizes, heavy child, par, lvl
 *   3) timer = 0; head[r] = r; decompose(r, -1);
 *   4) build a segtree of size n; put value of node u at position in[u].
 *      tree[pos] tells you WHICH node sits at segtree position pos (for initial build).
 *
 * QUERY PATH u..v:
 *   for (auto [l, r] : getRanges(u, v)) ans = merge(ans, seg.query(l, r));
 *   NOTE: the ranges come in arbitrary order (we jump from both ends) ->
 *         fine for COMMUTATIVE ops (sum/min/max/gcd). For non-commutative
 *         (e.g. hashing along the path) you must collect and order them carefully.
 *
 * EDGE-WEIGHTED version (costs on edges, not nodes) — 2 changes:
 *   1) store each edge's weight on the DEEPER endpoint (child), root holds identity
 *   2) in getRanges, the shared-chain range must EXCLUDE the LCA itself:
 *      use the commented `in[u]+1` line instead (LCA's slot holds the edge ABOVE lca,
 *      which is not on the path).
 *
 * BONUS TRICK (free with this ordering): the subtree of u is the contiguous range
 *   [in[u], in[u] + sz[u] - 1]  ->  subtree queries/updates with the same segtree!
 *
 * Multi-test: reset timer = 0 (and clear adj).
 */
int n, timer, sz[N], in[N], tree[N], big[N], head[N], par[N], lvl[N];
vector<int> adj[N];

// sizes, heavy child, parent, level
void dfs0(int u, int p) {
    sz[u] = 1;
    big[u] = -1;                       // -1 = leaf, no heavy child
    for (int v : adj[u]) if (v != p) {
        par[v] = u;
        lvl[v] = lvl[u]+1;
        dfs0(v, u);
        sz[u] += sz[v];
        if (big[u] == -1 || sz[v] > sz[big[u]]) big[u] = v;   // heaviest child
    }
}

// write nodes to positions: heavy chain first => chain is contiguous in `in` order
void decompose(int u, int p) {
    tree[timer] = u;                   // tree[pos] = node at segtree position pos
    in[u] = timer++;
    if (~big[u]) {
        head[big[u]] = head[u];        // heavy child continues MY chain
        decompose(big[u], u);
    }

    for (int v : adj[u]) if (v != p && v != big[u]) {
        head[v] = v;                   // light child starts its own chain
        decompose(v, u);
    }
}

// O(log n) segtree ranges covering the path u..v (inclusive)
vector<pair<int,int>> getRanges(int u, int v) {
    vector<pair<int,int>> ranges;
    while (true) {
        if (head[u] == head[v]) {      // same chain -> final contiguous piece, contains the LCA
            if (lvl[u] > lvl[v]) swap(u, v);   // u = higher one = the LCA itself
            ranges.emplace_back(in[u], in[v]);
            // EDGE QUERIES: replace the line above with:
            // if (u != v) ranges.emplace_back(in[u] + 1, in[v]);   // skip the LCA slot
            break;
        }

        // jump up from the chain whose head is DEEPER (else we could skip past the LCA)
        if (lvl[head[u]] < lvl[head[v]]) swap(u, v);
        ranges.emplace_back(in[head[u]], in[u]);   // whole chain piece: head..u
        u = par[head[u]];                          // hop above the chain
    }
    return ranges;
}
