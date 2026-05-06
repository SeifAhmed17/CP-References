class Trie {
    const static int N = 26;
    const static int baseChar = 'a';
    class Node {
    public:
        Node* child[N];
        int count, isEnd;
        Node():isEnd(false), count(0) {
            memset(child,0,sizeof child);
        }
    };
    Node* root = new Node();

public:
    void insert(const string& s) {
        Node* cur = root;
        for (char ch : s) {
            int c = ch-baseChar;
            if (cur->child[c] == NULL) cur->child[c] = new Node();
            cur = cur->child[c];
            cur->count++;
        }
        cur->isEnd++;
    }

    void del(Node* cur, const string& s, int i) {

        if (i == (int)s.size()) {
            cur->isEnd--;
            return;
        }

        int c = s[i] - baseChar;
        Node* nxt = cur->child[c];
        del(nxt, s, i+1);

        nxt->count--;

        if (!nxt->count) {
            delete nxt;
            cur->child[c] = NULL;
        }
    }

    void del(const string& s) {
        del(root,s,0);
    }

    bool search(const string& s) {
        Node* cur = root;
        for (char ch : s) {
            int c = ch - baseChar;
            if (cur->child[c] == NULL) return false;
            cur = cur->child[c];
        }
        return cur->isEnd;
    }
};