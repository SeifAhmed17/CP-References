/*
 * LAZY SEGMENT TREE — RANGE update, range query. O(log n) each.
 * -------------------------------------------------------------
 * 0-INDEXED, query/update(l, r) INCLUSIVE. As written: RANGE ADD + RANGE SUM.
 *
 * USAGE:
 *   SegmentTree st(a);        // builds from vector a in O(n)
 *   st.update(l, r, x);       // a[i] += x for all i in [l, r]
 *   st.query(l, r);           // sum a[l..r]
 *
 * RECALL — lazy propagation:
 *   A node's val is always CORRECT for its whole segment; pending updates that
 *   its CHILDREN haven't seen yet sit in `lazy`. Before stepping into children
 *   (query or update), propagate() pushes the lazy one level down.
 *   change(x, len) = "apply update x to a whole segment of length len".
 *
 * ===== THE 3 SPOTS THAT DEFINE THE TREE (change these per problem) =====
 *   1) merge()        — how two children combine        (here: sum)
 *   2) Node neutral   — identity of merge               (sum->0, min->INF, max->-INF)
 *   3) change()       — how an update hits a segment + how lazies COMPOSE
 *
 * ===== COMMON VARIANTS =====
 * (A) range ADD + range SUM  (as written):
 *       change: val += x * len;  lazy += x;
 * (B) range ADD + range MIN/MAX:
 *       merge -> min/max, neutral -> INF/-INF,
 *       change: val += x;  lazy += x;              // NO len — min shifts by x, not x*len
 * (C) range ASSIGN (a[i] = x) + range SUM:
 *       change: val = x * len;  lazy = x;          // lazies OVERWRITE instead of add
 *       and DEFAULT_LAZY must be a value that can never be assigned (isLazy already
 *       guards this — that's exactly why isLazy exists: 0 may be a legit assignment!)
 * (D) assign + min/max: change: val = x; lazy = x;
 *
 * PITFALLS:
 *   - val/lazy are ll here: range-add + sum overflows int almost immediately.
 *   - neutral Node() is returned for out-of-range parts of query — it MUST match merge.
 *   - Multiple lazy types (add AND assign together) need composition rules — derive
 *     carefully (assign kills pending add; add on top of assign folds into the assign).
 */
struct Node {
    static ll DEFAULT_VALUE, DEFAULT_LAZY;
    ll val, lazy;
    bool isLazy;

    Node(ll x = DEFAULT_VALUE) : val(x), lazy(DEFAULT_LAZY), isLazy(false) {}

    // apply update x to this ENTIRE segment (len = number of leaves under it)
    void change(ll x, int len) {
        val += x * len;        // (A) sum. | (B) min/max: val += x | (C) assign+sum: val = x*len
        lazy += x;             // compose with pending lazy.       | (C)/(D) assign: lazy = x
        isLazy = true;
    }
};
ll Node::DEFAULT_VALUE = 0, Node::DEFAULT_LAZY = 0;   // neutral val / neutral lazy

class SegmentTree {
private:
    int TREESIZE;
    vector<Node> tree;

    Node merge(const Node &nl, const Node &nr) { return Node(nl.val + nr.val); }  // CHANGE

    void Build(const vector<ll> &a, int idx, int lx, int rx) {
        if (lx == rx) {
            if (lx < (int) a.size()) tree[idx] = Node(a[lx]);
            else tree[idx] = Node();               // padding leaves = neutral
            return;
        }

        int mid = (lx + rx) >> 1;
        Build(a, 2 * idx + 1, lx, mid);
        Build(a, 2 * idx + 2, mid + 1, rx);

        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    // push this node's pending lazy down ONE level (children lengths differ!)
    void propagate(int idx, int lx, int rx) {
        if (lx == rx || !tree[idx].isLazy) return;

        int mid = (lx + rx) >> 1;
        tree[2 * idx + 1].change(tree[idx].lazy, mid - lx + 1);
        tree[2 * idx + 2].change(tree[idx].lazy, rx - mid);

        tree[idx].isLazy = false;
        tree[idx].lazy = Node::DEFAULT_LAZY;
    }

    Node query(int l, int r, int idx, int lx, int rx) {
        propagate(idx, lx, rx);                    // ALWAYS push before descending

        if (lx >= l && rx <= r) return tree[idx];  // fully inside
        if (rx < l || lx > r) return Node();       // fully outside -> neutral

        int mid = (lx + rx) >> 1;
        Node nLeft = query(l, r, 2 * idx + 1, lx, mid);
        Node nRight = query(l, r, 2 * idx + 2, mid + 1, rx);

        return merge(nLeft, nRight);
    }

    void update(int l, int r, ll newVal, int idx, int lx, int rx) {
        propagate(idx, lx, rx);

        if (lx >= l && rx <= r) {                  // fully inside -> lazy-apply and stop
            tree[idx].change(newVal, rx - lx + 1);
            return;
        }
        if (rx < l || lx > r) return;

        int mid = (lx + rx) >> 1;
        update(l, r, newVal, 2 * idx + 1, lx, mid);
        update(l, r, newVal, 2 * idx + 2, mid + 1, rx);

        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

public:
    SegmentTree(const vector<ll> &a) {
        TREESIZE = 1;
        while (TREESIZE < (int) a.size()) TREESIZE <<= 1;   // pad to power of two
        tree.resize(2 * TREESIZE);
        Build(a, 0, 0, TREESIZE - 1);
    }

    ll query(int l, int r) { return query(l, r, 0, 0, TREESIZE - 1).val; }

    void update(int l, int r, ll newVal) { update(l, r, newVal, 0, 0, TREESIZE - 1); }
};
