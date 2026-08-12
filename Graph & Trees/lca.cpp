/*
 * LCA + K-TH ANCESTOR (binary lifting)
 * ------------------------------------
 * anc[k][v] = the 2^k-th ancestor of v.  Build O(n log n), query O(log n).
 *
 * RECALL — how it works:
 *   anc[0][v] = parent. anc[k][v] = anc[k-1][ anc[k-1][v] ]  ("jump 2^(k-1) twice").
 *   We can fill v's whole column during the DFS because all of v's ancestors
 *   are already fully computed when we reach v.
 *   kth ancestor: decompose k in binary, jump by each set bit.
 *   LCA(u, v): lift the deeper one to the same level; if equal -> done;
 *   else jump BOTH up by the largest powers that DON'T make them meet;
 *   they end up just below the LCA -> answer is anc[0][u].
 *
 * SETUP (sizes here are placeholders — declare AFTER reading n in real code):
 *   LOG = __lg(n) + 2;                  // 2^LOG > n  (n=2e5 -> LOG=19)
 *   anc.assign(LOG, vector<int>(n));
 *   lvl[root] = 0; anc[0][root] = root; // root's "parent" = itself, so jumps CLAMP at root
 *   dfs0(root, -1);
 *
 * HANDY: dist(u, v) = lvl[u] + lvl[v] - 2 * lvl[lca(u,v)]
 *        kth node on path u->v: if k <= lvl[u]-lvl[l] lift from u, else lift dist-k from v.
 *
 * NOTE: because root points to itself, kth_anc with k > depth just returns the root
 *       (never crashes) — often exactly what you want.
 */
int n, LOG;
vector<vector<int>>anc(LOG, vector<int>(n)), adj(n);
vector<int> lvl(n);

void dfs0(int u, int p) {

    for (auto v : adj[u]) if (v != p) {

        lvl[v] = lvl[u] + 1;
        anc[0][v] = u;

        for (int k=1; k<LOG; k++)
            anc[k][v] = anc[k-1][anc[k-1][v]];    // 2^k = two jumps of 2^(k-1)

        dfs0(v, u);
    }
}

// jump k edges up from u (clamps at root)
int kth_anc(int k, int u) {
    for(int i=0; i<LOG; i++) if(k >> i & 1) u = anc[i][u];
    return u;
}

int get_lca(int u, int v){
    if (lvl[u] > lvl[v]) swap(u, v);       // make v the deeper one
    v = kth_anc(lvl[v]-lvl[u], v);         // equalize levels
    if(u == v) return u;                   // u was an ancestor of v

    // biggest-first: jump both up while they stay DIFFERENT
    for(int i=LOG-1; i>=0; i--)
        if(anc[i][u] != anc[i][v])
            u = anc[i][u], v = anc[i][v];

    return anc[0][u];                      // now both sit right below the LCA
}
