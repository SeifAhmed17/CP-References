const int b1 = 41, b2 = 37, mod1 = 1e9+7, mod2 = 1e9+9;
int pw1[N], pw2[N];

void init() {
    pw1[0] = pw2[0] = 1;
    for (int i=1; i<N; i++) {
        pw1[i] = 1LL * pw1[i-1] * b1 % mod1;
        pw2[i] = 1LL * pw2[i-1] * b2 % mod2;
    }
}

class Hash
{
    int n;
    vector<int> h1, h2;

public:
    Hash(const string& s): n(s.size()), h1(n), h2(n) {
        h1[0] = h2[0] = (unsigned char)s[0] + 1;
        for (int i=1; i<n; i++) {
            int d = (unsigned char)s[i] + 1;
            h1[i] = (1LL*h1[i-1]*b1%mod1 + d)%mod1;
            h2[i] = (1LL*h2[i-1]*b2%mod2 + d)%mod2;
        }
    }

    pair<int,int> get(int l, int r) {
        int x = (h1[r] - (1LL*(l?h1[l-1]:0)*pw1[r-l+1]%mod1) + mod1) % mod1;
        int y = (h2[r] - (1LL*(l?h2[l-1]:0)*pw2[r-l+1]%mod2) + mod2) % mod2;
        return {x, y};
    }
};