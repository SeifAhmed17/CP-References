vector<int> d = a;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
    }