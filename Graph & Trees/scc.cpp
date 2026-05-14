void condense(int& n, vector<vector<int>>& adj, vector<int>& compId, vector<vector<int>>& sccs) {

    vector<bool> inStack(n);
    stack<int> st;
    vector<int> in(n), low(n);
    int id = 0, timer = 1;

    function<void(int)> tarjan = [&](int u) {
        in[u] = low[u] = timer++;
        st.push(u); inStack[u] = true;
        for (int v : adj[u]) {
            if (!in[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (inStack[v]) {
                low[u] = min(low[u], in[v]);
            }
        }

        if (in[u] == low[u]) {
            vector<int> comp;
            while (!st.empty()) {
                int x = st.top(); st.pop();
                inStack[x] = false;
                comp.emplace_back(x);
                compId[x] = id;
                if (x == u) break;
            }
            sccs.emplace_back(comp);
            id++;
        }
    };

    for (int i=0; i<n; i++) if (!in[i]) tarjan(i);


    set<pair<int,int>> seen;
    vector<vector<int>> nAdj(id);
    for (int u=0; u<n; u++) {
        for (int v : adj[u]) {
            if (compId[u] != compId[v] && seen.find({compId[u], compId[v]}) == seen.end()) {
                nAdj[compId[u]].emplace_back(compId[v]);
                seen.insert({compId[u], compId[v]});
            }
        }
    }

    n = id;
    adj = nAdj;
}