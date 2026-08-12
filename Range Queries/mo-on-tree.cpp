/*
 * MO'S ON A TREE — offline PATH queries u..v, O((n + q) * sqrt(n))
 * ----------------------------------------------------------------
 * Classic: SPOJ COT2 — # distinct values on the path. Needs: const SQ (~sqrt(2n)), LOG.
 *
 * RECALL — the flattening trick (Euler tour with BOTH stamps):
 *   Every node u is written TWICE: at in[u] (entering) and out[u] (leaving).
 *   flat[] has length 2n. For a path query u..v (say in[u] <= in[v]):
 *     - u is an ancestor of v (lca == u):  window = [ in[u],  in[v] ]
 *     - otherwise:                         window = [ out[u], in[v] ]  + add LCA manually
 *   KEY FACT: inside that window, nodes ON the path appear exactly ONCE;
 *   nodes OFF the path appear TWICE (their whole subtree got entered and left).
 *   So process() toggles: 1st appearance -> node enters, 2nd -> node leaves.
 *   That's the freqNode parity check. The LCA is the only path node missing in
 *   case 2, hence the manual add/del around answering.
 *
 * PITFALLS:
 *   - a[i] values used as indices into cnt arrays -> COORDINATE-COMPRESS them if
 *     they can exceed n (here input is just shifted to 0-based: values assumed 1..n;
 *     replace with compression when values go to 1e9).
 *   - add/del receive a POSITION in flat[]; x = flat[i] is the VALUE at that spot.
 *   - Don't forget to define SQ and LOG (LOG = __lg(n)+2).
 */
struct Query {
    int l, r, iq, lca;                // window [l,r] in flat[], iq = original index,
                                      // lca = -1 if ancestor case (LCA already inside window)
    bool operator<(const Query& other) const {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return ((l/SQ)&1) ? r > other.r : r < other.r;    // snake order (see mo.cpp)
    }
};

void solve()
{
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin >> a[i], --a[i];   // values -> 0-based (COMPRESS if large!)
    vector<vector<int>> adj(n);
    for (int i=0; i<n-1; i++) {
        int u, v; cin >> u >> v;
        adj[--u].pb(--v);
        adj[v].pb(u);
    }

    // ---- Euler tour (in & out stamps) + binary lifting for LCA ----
    int timer = 0;
    vector<int> in(n), out(n), lvl(n), flat(2*n), node(2*n);  // node[pos] = which node sits there
    vector<vector<int>> anc(LOG, vector<int>(n));
    function<void(int,int)> dfs0 = [&](int u, int p) {
        in[u] = timer;
        node[timer++] = u;
        for (int v : adj[u]) if (v != p) {
            lvl[v] = lvl[u] + 1;

            anc[0][v] = u;
            for (int i=1; i<LOG; i++)
                anc[i][v] = anc[i-1][anc[i-1][v]];

            dfs0(v, u);
        }

        out[u] = timer;
        node[timer++] = u;
    };
    dfs0(0, -1);

    for (int i=0; i<n; i++) flat[in[i]] = flat[out[i]] = a[i];  // value copied to both stamps

    auto kth_ancestor = [&](int k, int u) {
        for (int i=0; i<LOG; i++) if (k>>i&1) u = anc[i][u];
        return u;
    };

    auto get_lca = [&](int u, int v) {
        if (lvl[u] > lvl[v]) swap(u, v);
        v = kth_ancestor(lvl[v]-lvl[u], v);
        if (u == v) return u;
        for (int i=LOG-1; i>=0; i--)
            if (anc[i][u] != anc[i][v])
                u = anc[i][u], v = anc[i][v];
        return anc[0][u];
    };

    // ---- build the windows (the case split from the header) ----
    vector<Query> queries(q);
    for (int i=0; i<q; i++) {
        int u, v; cin >> u >> v, --u, --v;
        if (in[u] > in[v]) swap(u, v);           // ensure in[u] <= in[v]
        int lca = get_lca(u, v);
        if (lca == u) {
            queries[i] = {in[u], in[v], i, -1};  // ancestor case: LCA(=u) is in the window
        }
        else {
            queries[i] = {out[u], in[v], i, lca};// general case: add LCA by hand later
        }
    }
    sort(all(queries));


    vector<int> answer(q), freqNode(n);          // freqNode = appearances of node in window (0/1/2)

    // FILL THESE (same roles as plain Mo): maintain answer over the SET of path nodes
    auto add = [&](int i) {
        int x = flat[i];
        // x = the VALUE entering, e.g.: if (++cnt[x] == 1) distinct++;
    };

    auto del = [&](int i) {
        int x = flat[i];
        // x = the VALUE leaving,  e.g.: if (--cnt[x] == 0) distinct--;
    };

    // parity toggle: 1st time node appears -> enters; 2nd time -> cancels out
    auto process = [&](int i) {
        int u = node[i];
        if (++freqNode[u] & 1) add(in[u]);
        else del(in[u]);
    };

    auto get_answer = [&] {
        return 0; // current answer, e.g. distinct
    };

    int L = 0, R = -1;                           // 0-indexed empty window (flat is 0-indexed!)
    for (const auto& [l, r, iq, lca] : queries) {
        while (l < L) process(--L);
        while (R < r) process(++R);
        while (L < l) process(L++);
        while (r < R) process(R--);
        if (~lca) add(in[lca]);                  // LCA joins just for the answer...
        answer[iq] = get_answer();
        if (~lca) del(in[lca]);                  // ...and leaves again (keeps window clean)
    }

    for (int x : answer) cout << x << '\n';
}
