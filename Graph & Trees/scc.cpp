/*
 * SCC + CONDENSATION (Tarjan, one DFS, O(n + m))
 * ----------------------------------------------
 * SCC = maximal set of nodes in a DIRECTED graph where everyone reaches everyone.
 * Condensation = shrink each SCC to one node -> always a DAG.
 *
 * WHAT THIS FUNCTION DOES (in/out parameters — it REPLACES n and adj!):
 *   in : n, adj = original directed graph (0-indexed)
 *   out: n, adj = condensation DAG (multi-edges deduped via `seen`)
 *        compId[u] = component of original node u   (size n_original, pre-sized by caller!)
 *        sccs[c]   = list of original nodes in component c
 *   Keep copies of the originals if you still need them.
 *
 * CALL:
 *   vector<int> compId(n); vector<vector<int>> sccs;
 *   condense(n, adj, compId, sccs);
 *
 * KEY PROPERTY (Tarjan gives it for free):
 *   components are produced in REVERSE topological order ->
 *   for every condensed edge cu -> cv:  compId[u] > compId[v].
 *   So looping c = 0..n-1 processes SINKS FIRST — perfect for DAG DP where
 *   dp[c] depends on successors (e.g. "best value reachable from c").
 *   Loop c = n-1..0 for sources-first.
 *
 * RECALL — how Tarjan works:
 *   low[u] = lowest discovery time reachable from u using tree edges + back edges
 *   to nodes STILL ON THE STACK (inStack check — cross edges to finished SCCs don't count).
 *   When low[u] == in[u], u is the "root" of an SCC -> pop the stack down to u.
 *
 * CLASSIC USES: 2-SAT, "min nodes to start from to reach all" (= #source comps),
 *   "add min edges to make strongly connected" (= max(#sources, #sinks), 1 comp -> 0).
 */
void condense(int& n, vector<vector<int>>& adj, vector<int>& compId, vector<vector<int>>& sccs) {

    vector<bool> inStack(n);
    stack<int> st;
    vector<int> in(n), low(n);      // in = discovery time, 0 = unvisited (timer starts at 1)
    int id = 0, timer = 1;

    function<void(int)> tarjan = [&](int u) {
        in[u] = low[u] = timer++;
        st.push(u); inStack[u] = true;
        for (int v : adj[u]) {
            if (!in[v]) {                          // tree edge
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (inStack[v]) {                 // back/cross edge into current stack
                low[u] = min(low[u], in[v]);
            }
            // else: v's SCC already finished -> ignore
        }

        if (in[u] == low[u]) {                     // u is the root of an SCC -> pop it
            vector<int> comp;
            while (!st.empty()) {
                int x = st.top(); st.pop();
                inStack[x] = false;
                comp.emplace_back(x);
                compId[x] = id;
                if (x == u) break;
            }
            sccs.emplace_back(comp);
            id++;
        }
    };

    for (int i=0; i<n; i++) if (!in[i]) tarjan(i);

    // build condensation, dedup parallel edges between the same pair of comps
    set<pair<int,int>> seen;
    vector<vector<int>> nAdj(id);
    for (int u=0; u<n; u++) {
        for (int v : adj[u]) {
            if (compId[u] != compId[v] && seen.find({compId[u], compId[v]}) == seen.end()) {
                nAdj[compId[u]].emplace_back(compId[v]);
                seen.insert({compId[u], compId[v]});
            }
        }
    }

    n = id;          // n and adj now describe the DAG!
    adj = nAdj;
}
