mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T> T rand(T l, T r) { return uniform_int_distribution<T>(l, r)(rng); }

struct Hash {
    ll a, b, c, d, e;
    Hash(ll _a, ll _b, ll _c, ll _d, ll _e):a(_a),b(_b),c(_c),d(_d),e(_e){}
    Hash() {
        a = rand(1, (int)1e9);
        b = rand(1, (int)1e9);
        c = rand(1, (int)1e9);
        d = rand(1, (int)1e9);
        e = rand(1, (int)1e9);
    }
    Hash operator+(const Hash& other) const {
        return Hash(a+other.a,b+other.b,c+other.c,d+other.d,e+other.e);
    }
    Hash operator-(const Hash& other) const {
        return Hash(a-other.a,b-other.b,c-other.c,d-other.d,e-other.e);
    }
    bool operator==(const Hash& other) const {
        return a==other.a&&b==other.b&&c==other.c&&d==other.d&&e==other.e;
    }
};