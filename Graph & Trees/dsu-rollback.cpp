/*
 * DSU WITH ROLLBACK — undo merges in reverse order, O(log n) per op
 * ----------------------------------------------------------------
 * !! NO path compression (it can't be undone cheaply) — that's why find is
 *    O(log n), NOT ~O(1). Union by size keeps the tree shallow; DON'T "optimize".
 * !! Rollback is LIFO only: you can undo the LAST merges, not an arbitrary one.
 *
 * USAGE:
 *   init(n);
 *   merge(u, v);                   // as usual (failed merges are fine)
 *   int t = snapshot();            // remember a point in time
 *   ... more merges ...
 *   rollback(t);                   // undo everything after the snapshot
 *
 * RECALL — where this shows up:
 *   - Mo with rollback (mo-with-rollback.cpp): add left-side elements, answer, undo.
 *   - OFFLINE dynamic connectivity ("edge exists during time interval [l, r]"):
 *     put each edge on the O(log q) nodes of a segment tree over TIME covering
 *     its interval; DFS the tree merging that node's edges, answer queries at
 *     leaves, rollback(t) when leaving the node. Handles deletions with a DSU!
 *   - Bipartiteness / parity under edge insert+undo: same trick, store parity too.
 */
namespace DSU
{
    vector<int> par, len;
    vector<pair<int,int>> hist;        // (root that got absorbed, root it went under)

    void init(int n) {
        par.assign(n+3, 0), len.assign(n+3, 1);
        iota(all(par), 0);
        hist.clear();
    }
    int find(int u) {                  // NO compression — walk up every time
        while (par[u] != u) u = par[u];
        return u;
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;      // failed merges push nothing (nothing to undo)
        if (len[u] < len[v]) swap(u, v);
        par[v] = u, len[u] += len[v];
        hist.push_back({v, u});
        return true;
    }

    int snapshot() { return hist.size(); }
    void rollback(int t) {             // undo until only t merges remain
        while ((int)hist.size() > t) {
            auto [v, u] = hist.back(); hist.pop_back();
            par[v] = v, len[u] -= len[v];
        }
    }
}
using namespace DSU;
