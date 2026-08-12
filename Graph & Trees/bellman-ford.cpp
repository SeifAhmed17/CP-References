/*
 * BELLMAN-FORD — shortest paths WITH negative edges + negative cycle detection, O(n*m)
 * ------------------------------------------------------------------------------------
 * RECALL: relax every edge, n-1 rounds. A shortest path has <= n-1 edges, so after
 * round k all shortest paths using <= k edges are final. If ROUND n STILL relaxes
 * something -> a negative cycle is reachable from src.
 *
 * USAGE:
 *   vector<ll> dist;
 *   bool hasNegCycle = bellmanFord(n, src, edges, dist);
 *   dist[u] == INF -> unreachable.
 *
 * !! the `dist[u] != INF` guard is mandatory: without it INF + (negative w)
 *    "improves" unreachable nodes and everything is garbage.
 *
 * NOTES:
 *   - returns true = SOME negative cycle reachable from src. Nodes whose real
 *     distance is -infinity: collect every v relaxed in the extra pass, then
 *     BFS/DFS forward from them — everything visited has dist = -inf.
 *   - negative cycle ANYWHERE in the graph (no source): init ALL dist to 0
 *     (equivalent to a virtual source with 0-edges to everyone) and run the same loop.
 *   - need the cycle itself: remember par[v] on relaxations; from a node relaxed in
 *     the extra pass, follow par n times (guaranteed to land ON the cycle), then loop.
 */
struct Edge { int u, v; ll w; };

bool bellmanFord(int n, int src, vector<Edge>& edges, vector<ll>& dist) {
    dist.assign(n, INF);
    dist[src] = 0;

    for (int it=0; it<n-1; it++) {
        bool any = false;
        for (auto& [u, v, w] : edges)
            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w, any = true;
        if (!any) break;                 // already stable -> no cycle possible either
    }

    for (auto& [u, v, w] : edges)        // round n: anything still moving = neg cycle
        if (dist[u] != INF && dist[u] + w < dist[v])
            return true;
    return false;
}
