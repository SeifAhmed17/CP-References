/*
 * DSU / UNION-FIND (path compression + union by size)
 * ---------------------------------------------------
 * Maintains disjoint sets under "merge two sets" + "which set is u in".
 * Both ops amortized ~O(1) (inverse Ackermann).
 *
 * USAGE:
 *   init(n);                       // MUST call first (and again for every test case!)
 *   find(u)                        // representative of u's set; find(u)==find(v) <=> same set
 *   merge(u, v)                    // returns false if already in the same set
 *   len[find(u)]                   // size of u's component (only valid at the ROOT!)
 *
 * RECALL — classic uses:
 *   - Kruskal MST: sort edges by weight, add edge iff merge(u,v) succeeds.
 *   - Count components: components -= merge(u,v) succeeded.
 *   - Offline "connectivity after adding edges" queries.
 *   - Cycle detection in undirected graph: merge fails -> edge closes a cycle.
 *   - Bipartite / parity trick: node u -> two nodes (u, u+n) "u is white / u is black".
 */
namespace DSU
{
    int sz; vector<int> par, len;   // par = parent pointer, len = component size (valid at root)

    void init(int n)
    {
        sz = n+3;
        par.assign(sz, 0), len.assign(sz, 1);
        iota(all(par), 0);          // everyone is their own parent
    }

    int find(int u) {
        // path compression: hang u (and the whole chain) directly off the root
        return par[u] == u ? u : par[u] = find(par[u]);
    }

    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;          // already connected
        if (len[u] < len[v]) swap(u, v);   // union by size: small tree under big tree
        par[v] = u, len[u] += len[v];
        return true;
    }
}
using namespace DSU;
