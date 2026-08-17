/*
 * SLIDING WINDOW MIN/MAX — monotonic deque, O(n) total
 * ----------------------------------------------------
 * Min of every window of size k. Deque holds INDICES with a[.] strictly
 * increasing front->back, so the front is always the window minimum.
 * An element killed from the back can never be an answer again (something
 * newer AND smaller-or-equal exists) — that's the whole proof.
 *
 * USAGE: windowMin(a, k) -> res[i] = min of a[i .. i+k-1]  (size n-k+1).
 *        For max: flip the comparison (or negate the array).
 *
 * RECALL:
 *   - DP speedup: dp[i] = cost[i] + min(dp[i-k .. i-1]) -> keep the deque over
 *     dp instead of re-querying a segment tree: O(n) instead of O(n log n).
 *   - Variable-width windows (two pointers): same deque; pop front while its
 *     index < current left bound.
 *   - Monotonic STACK cousin — nearest smaller to the left for every i:
 *       while (!st.empty() && a[st.top()] >= a[i]) st.pop();  // top = answer, then push i
 *     Gives "span until a smaller element" -> largest rectangle in histogram.
 */
vector<ll> windowMin(vector<ll>& a, int k)
{
    int n = a.size();
    vector<ll> res;
    deque<int> dq;                        // indices, a[dq] increasing
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();  // > for max
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();                    // fell out of window
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
