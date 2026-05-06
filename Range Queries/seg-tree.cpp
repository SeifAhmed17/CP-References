class SegmentTree {

    struct Node {
        int val;
        Node(int x = 0) : val(x) {}
    };

    int TREESIZE;
    vector<Node> tree;

    Node merge(const Node& nl, const Node& nr) { return Node(nl.val + nr.val); }

    Node query(int l, int r, int idx, int lx, int rx) {
        if (rx < l || lx > r) return Node();
        if (lx >= l && rx <= r) return tree[idx];

        int mid = (lx + rx) >> 1;
        return merge(query(l, r, 2*idx+1, lx, mid), query(l, r, 2*idx+2, mid+1, rx));
    }

    void update(int pos, int newVal, int idx, int lx, int rx) {
        if (lx == rx) {
            tree[idx] = Node(newVal);
            return;
        }

        int mid = (lx + rx) >> 1;
        if (pos <= mid) update(pos, newVal, 2*idx+1, lx, mid);
        else update(pos, newVal, 2*idx+2, mid+1, rx);

        tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
    }

public:

    SegmentTree(){}

    void init(const int& n) {
        TREESIZE = 1;
        while (TREESIZE < n) TREESIZE <<= 1;
        tree.assign(4 * TREESIZE, Node());
    }

    int query(int l, int r) { return query(l, r, 0, 0, TREESIZE-1).val; }

    void update(int pos, int newVal) { update(pos, newVal, 0, 0, TREESIZE-1); }
};