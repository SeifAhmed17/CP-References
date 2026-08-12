/*
 * ARTICULATION POINTS (cut vertices) — Tarjan, O(n + m)
 * -----------------------------------------------------
 * Cut vertex = node whose REMOVAL (with its edges) disconnects the graph.
 *
 * RECALL — same in/low machinery as bridges, DIFFERENT condition:
 *   non-root u is a cut vertex  <=>  SOME child v has  low[v] >= in[u]
 *     (v's subtree can't climb strictly ABOVE u -> removing u strands it)
 *   root is special: cut vertex  <=>  it has >= 2 DFS CHILDREN.
 *   >>> compare: bridge condition was low[v] > in[u] (strict!) on the EDGE. <<<
 *
 * NOTES:
 *   - parallel edges DON'T matter here (unlike bridges): removing the VERTEX
 *     kills all copies anyway, so skipping the parent by node is fine.
 *     Self-loops: just don't add them to adj.
 *   - a graph can have 0 cut vertices (biconnected) — e.g. a simple cycle.
 *   - one node can be "the" cut vertex for many components; count via how many
 *     children satisfy the condition (+1 for the rest of the graph) if a problem
 *     asks "into how many pieces does removing u split the graph".
 *
 * CALL:  for (int i=0; i<n; i++) if (!in[i]) dfsCut(i, -1);
 */
int n, timer = 1, in[N], low[N];
bool isCut[N];
vector<int> adj[N];

void dfsCut(int u, int p) {
    in[u] = low[u] = timer++;
    int children = 0;
    for (int v : adj[u]) if (v != p) {
        if (in[v])
            low[u] = min(low[u], in[v]);          // back edge
        else {
            dfsCut(v, u); children++;
            low[u] = min(low[u], low[v]);
            if (p != -1 && low[v] >= in[u])       // v's subtree is trapped under u
                isCut[u] = true;
        }
    }
    if (p == -1 && children > 1) isCut[u] = true; // root rule
}
