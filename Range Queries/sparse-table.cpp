class SparseTable {

    private:
        vector<vector<int>> t;
        int n, LOG;
        int merge(int e, int o) { return min(e, o); }
    
    public:
    
        SparseTable(vector<int>& a) {
            n = a.size(), LOG = 32 - __builtin_clz(n);
            t.resize(LOG, vector<int>(n));
    
            for (int i=0; i<n; i++) t[0][i] = a[i];
    
            for (int k=1; (1<<k)<=n; k++) {
                for (int i=0; i+(1<<k)<=n; i++) {
                    t[k][i] = merge(t[k-1][i], t[k-1][i+(1<<(k-1))]);
                }
            }
        }
    
        int query(int l, int r) {
            int k = __lg(r-l+1);
            return merge(t[k][l], t[k][r-(1<<k)+1]);
        }
    };