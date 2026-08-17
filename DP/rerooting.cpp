/*
 * REROOTING — answer "as if rooted at u" for EVERY u, O(n) total
 * --------------------------------------------------------------
 * Two DFS passes: (1) normal tree DP computing down[u] = answer inside u's
 * subtree; (2) push a parent-side value up[v] down the tree, combining what
 * the parent knows MINUS v's own contribution.
 *
 * As written: ans[u] = SUM of distances from u to every node (classic).
 *   down pass:  sz[u], down[u] = sum of dist to nodes in u's subtree
 *   push down:  ans[v] = ans[u] - sz[v] + (n - sz[v])
 *               (crossing edge u-v: v's subtree gets 1 closer, the rest 1 farther)
 *
 * RECALL — adapting it:
 *   - Works directly whenever the parent-side value is computable by
 *     "whole answer at parent MINUS child's contribution" (sum-like combines).
 *   - Combine NOT invertible (max depth, gcd, ...)? Then for each u build
 *     PREFIX and SUFFIX combines over its children's values; child v gets
 *     pref[i-1] + suf[i+1] + parent's up-value. Same O(n), just more bookkeeping.
 *   - Values on EDGES: fold the edge weight where the +1s are.
 */
namespace Reroot
{
    int n; vector<vector<int>> adj;
    vector<ll> down, ans; vector<int> sz;

    void dfs1(int u, int p) {
        sz[u] = 1, down[u] = 0;
        for (int v : adj[u]) if (v != p) {
            dfs1(v, u);
            sz[u] += sz[v];
            down[u] += down[v] + sz[v];       // every node in v's subtree is 1 farther
        }
    }
    void dfs2(int u, int p) {
        for (int v : adj[u]) if (v != p) {
            // reroot u -> v: v's subtree (sz[v] nodes) gets closer, rest gets farther
            ans[v] = ans[u] - sz[v] + (n - sz[v]);
            dfs2(v, u);
        }
    }

    void solve() {                            // fill n and adj first (0-indexed)
        sz.assign(n, 0), down.assign(n, 0), ans.assign(n, 0);
        dfs1(0, -1);
        ans[0] = down[0];
        dfs2(0, -1);                          // now ans[u] is correct for every u
    }
}
