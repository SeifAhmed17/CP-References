class LCA
{
    int nSize, logSize, root;
    vector<vector<int>>anc;
    vector<int> lvl;

    void Build(int u, int p, vector<vector<int>>& adj) {
        
        for (auto v : adj[u]) {
            if (v == p) continue;

            lvl[v] = lvl[u] + 1;
            anc[0][v] = u;

            for (int k=1; k<logSize; k++)
                anc[k][v] = anc[k-1][anc[k-1][v]];

            Build(v, u, adj);
        }
    }

public:
    LCA(int n, int r, vector<vector<int>>& adj): root(r), nSize(n+17), logSize(__lg(nSize)+2) {
        anc = vector<vector<int>>(logSize, vector<int>(nSize, root));
        lvl = vector<int>(nSize, 0);
        Build(r, r, adj);
    }

    int KthAncestor(int u, int k) {
        for (int i=logSize-1; i>=0; i--) {
            if (k >> i & 1)
                u = anc[i][u];
        }
        return u;
    }

    int get_lca(int u, int v) {
        if (lvl[v] > lvl[u]) swap(v, u);

        u = KthAncestor(u, lvl[u]-lvl[v]);

        if (u == v) return u;

        for (int i=logSize-1; i>=0; i--) {
            if (anc[i][u] != anc[i][v])
                u = anc[i][u], v = anc[i][v];
        }

        return anc[0][u];
    }
};