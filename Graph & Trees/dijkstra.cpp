/*
 * DIJKSTRA — single-source shortest paths, O((n + m) log n)
 * ---------------------------------------------------------
 * !! ONLY for NON-NEGATIVE edge weights. One negative edge -> use bellman-ford.cpp.
 *
 * USAGE:  build adj as {v, w} pairs; dijkstra(src, n); read dist[] / rebuild path via par[].
 *   dist[u] == INF  ->  unreachable.
 *
 * RECALL — lazy deletion: we push duplicates into the pq instead of decreasing keys.
 * The line `if (d > dist[u]) continue;` throws away stale entries — FORGETTING IT
 * is the classic bug (turns the algorithm exponential on some tests).
 *
 * VARIANTS:
 *   - multi-source ("nearest shop"): push ALL sources with dist 0 before the loop.
 *   - weights only 0/1 -> 0-1 BFS with a deque (push_front on 0-edges), O(n+m).
 *   - "k-th cheapest path" / state graphs: node = (vertex, state), same code.
 *   - path RECONSTRUCTION: walk par[] back from target, reverse.
 */
vector<pair<int,ll>> adj[N];         // {neighbor, weight}
ll dist[N];
int par[N];

void dijkstra(int src, int n) {
    fill(dist, dist+n, INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;   // min-heap {dist, node}
    dist[src] = 0; par[src] = -1;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;               // stale entry — DO NOT DELETE THIS LINE
        for (auto& [v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}
