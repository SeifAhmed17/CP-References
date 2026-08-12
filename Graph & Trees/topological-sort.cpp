/*
 * TOPOLOGICAL SORT (Kahn / BFS on in-degrees) — O(n + m)
 * ------------------------------------------------------
 * Order of a DAG where every edge u->v has u BEFORE v.
 *
 * USAGE:
 *   auto order = toposort(n, adj);
 *   if (sz(order) < n)  ->  THE GRAPH HAS A CYCLE (that's the standard cycle check!)
 *
 * VARIANTS:
 *   - LEXICOGRAPHICALLY SMALLEST order: replace queue with
 *     priority_queue<int, vector<int>, greater<>> — O(n log n + m).
 *   - DP over a DAG (longest path, counting paths): process nodes in this order,
 *     push dp along edges. Longest path in DAG = classic "critical path".
 *   - DFS alternative: postorder DFS, reverse it (same as SCC condensation order —
 *     note scc.cpp already hands you a reverse-topological component order for free).
 */
vector<int> toposort(int n, vector<vector<int>>& adj) {
    vector<int> indeg(n);
    for (int u=0; u<n; u++)
        for (int v : adj[u]) indeg[v]++;

    queue<int> q;                            // priority_queue<...> for lexicographic
    for (int i=0; i<n; i++) if (!indeg[i]) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.pb(u);
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return order;                            // size < n  <=>  cycle exists
}
