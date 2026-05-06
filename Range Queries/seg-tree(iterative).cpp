class SegmentTree {

    struct Node {
        int val;
        Node(int x = 0) : val(x) {}
    };

    int n;
    vector<Node> tree;

    Node merge(const Node& nl, const Node& nr) { return Node(nl.val + nr.val); }
    
    Node queryy(int l, int r) {
        Node res = Node();
        for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) res = merge(res, tree[l++]);
            if (r&1) res = merge(res, tree[--r]);
        }
        return res;
    }

public:
    SegmentTree(const int& _n){ init(_n); }

    void init(const int& _n) {
        n = _n;
        tree.assign(n<<1, Node());
    }

    void update(int pos, int val) {
        pos += n;
        tree[pos] = Node(val);
        while (pos > 1) {
            pos >>= 1;
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }
    
    int query(int l, int r) { return queryy(l, r+1).val; }
};