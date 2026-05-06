struct Query
{
    int l, r, idx;
    bool operator<(const Query& other) const {
        if (l/SQ != other.l/SQ) return l/SQ < other.l/SQ;
        return ((l/SQ) & 1) ? r > other.r : r < other.r;
    }
};

void MO(vector<Query>& queries, vector<int>& ans)
{
    sort(queries.begin(), queries.end());

    auto add = [&](int i) {
        //
    };

    auto del = [&](int i) {
        //
    };

    auto answer = [&]() {
        return 0;
    };

    int L = 1, R = 0;
    for (auto [l, r, idx] : queries) {
        while (l < L) add(--L);
        while (R < r) add(++R);
        while (L < l) del(L++);
        while (r < R) del(R--);

        ans[idx] = answer();
    }
}