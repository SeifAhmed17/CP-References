
int n, LOG;
vector<vector<int>>anc(LOG, vector<int>(n)), adj(n);
vector<int> lvl(n);

void dfs0(int u, int p) {
    
    for (auto v : adj[u]) if (v != p) {

        lvl[v] = lvl[u] + 1;
        anc[0][v] = u;

        for (int k=1; k<LOG; k++)
            anc[k][v] = anc[k-1][anc[k-1][v]];

        dfs0(v, u);
    }
}


int kth_anc(int k, int u) {
    for(int i=0; i<LOG; i++) if(k >> i & 1) u = anc[i][u];
    return u;
}    

int get_lca(int u, int v){
    if (lvl[u] > lvl[v]) swap(u, v);
    v = kth_anc(lvl[v]-lvl[u], v);
    if(u == v) return u;

    for(int i=LOG-1; i>=0; i--) 
        if(anc[i][u] != anc[i][v])
            u = anc[i][u], v = anc[i][v];

    return anc[0][u];
}

