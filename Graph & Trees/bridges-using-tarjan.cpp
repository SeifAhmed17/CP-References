/*
 * BRIDGES (Tarjan, one DFS, O(n + m))
 * -----------------------------------
 * Bridge = edge whose removal disconnects the graph.
 *
 * RECALL — how it works:
 *   in[u]  = DFS discovery time (also serves as "visited": 0 = unvisited, so timer starts at 1)
 *   low[u] = smallest discovery time reachable from u's subtree using tree edges
 *            + AT MOST ONE back edge.
 *   Edge (u -> child v) is a bridge  <=>  low[v] > in[u]
 *   (v's subtree has NO back edge climbing above v, so cutting the edge separates it.)
 *
 * SETUP:
 *   adj[u] holds {neighbor, edge id}. Edge id needed because we skip the PARENT EDGE,
 *   not the parent node -> parallel edges (u-v twice) are handled correctly:
 *   a doubled edge is NOT a bridge, and skipping by node would wrongly report it as one.
 *
 * CALL:  for (int i=0; i<n; i++) if (!in[i]) tarjan(i, -1);   // graph can be disconnected
 * READ:  isBridge[e] per edge id.
 *
 * NOTE: recursive — for n ~ 1e5+ on small stack limits, convert to iterative
 *       or use the lambda version (see bridge-tree.cpp).
 */
vector<pair<int,int>> adj[N];   // {v, edge id}
int n, m, timer = 1, in[N], low[N], isBridge[N];

void tarjan(int u, int pe) {    // pe = id of the edge we came from
    in[u] = low[u] = timer++;
    for (const auto& [v, e] : adj[u]) if (e != pe) {  // skip parent EDGE (not node!)
        if (in[v])
            low[u] = min(low[u], in[v]);   // back edge -> can climb to v's time
        else {
            tarjan(v, e);
            low[u] = min(low[u], low[v]);  // child's reach is our reach
            if (low[v] > in[u])            // child can't climb above u -> bridge
                isBridge[e] = true;
        }
    }
}
