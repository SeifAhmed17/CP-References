vector<vector<int>> mult(vector<vector<int>>& a, vector<vector<int>>& b) {
    const int n = a.size(), k = a[0].size(), m = b[0].size();
    vector<vector<int>> ret(n, vector<int>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            for (int z=0; z<k; z++) {
                ret[i][j] = (ret[i][j] + 1LL * a[i][z] * b[z][j] % mod) % mod;
            }
        }
    }
    return ret;
}

vector<vector<int>> binPow(vector<vector<int>>& a, ll b) {
    const int n = a.size(), m = a[0].size();
    vector<vector<int>> ret(n, vector<int>(m));
    for (int i=0; i<n; i++) ret[i][i] = 1;

    while (b) {
        if (b&1) ret = mult(ret, a);
        a = mult(a, a);
        b >>= 1;
    }

    return ret;
}