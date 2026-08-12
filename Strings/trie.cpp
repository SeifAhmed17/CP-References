/*
 * TRIE (prefix tree) — insert / search / delete words, O(|word|) each
 * -------------------------------------------------------------------
 * Node bookkeeping (this is what you usually query):
 *   count = how many inserted words PASS THROUGH this node
 *           -> "how many words start with prefix p": walk p, return count (0 if walk dies)
 *   isEnd = how many inserted words END exactly here (int, so duplicates are counted)
 *
 * CHANGE HERE: N (alphabet size) + baseChar — 'a' for lowercase, 'A', '0' for digits...
 *
 * PITFALLS:
 *   - del(s) assumes s WAS inserted (call search first if unsure) — deleting an
 *     absent word corrupts counts. It removes ONE occurrence and frees dead branches.
 *   - Memory: ~(total inserted chars) nodes * (26 pointers + 2 ints) ≈ 220B/char.
 *     1e6 total chars is fine; 1e7 is not — use arrays-of-int trie instead.
 *   - Multi-test: no clear() here — recreate the Trie object (leaks, but CP doesn't care)
 *     or add a recursive delete.
 *
 * COMMON EXTENSIONS (one-liners to add):
 *   - countPrefix(p): walk p, return cur->count
 *   - countWord(s):   walk s, return cur->isEnd
 *   - XOR problems on numbers -> binary-trie.cpp
 */
class Trie {
    const static int N = 26;            // CHANGE: alphabet size
    const static int baseChar = 'a';    // CHANGE: first char of alphabet
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
            cur->count++;               // one more word passes through
        }
        cur->isEnd++;
    }

    // internal: unwind the path, decrement counts, free branches that died
    void del(Node* cur, const string& s, int i) {

        if (i == (int)s.size()) {
            cur->isEnd--;
            return;
        }

        int c = s[i] - baseChar;
        Node* nxt = cur->child[c];
        del(nxt, s, i+1);

        nxt->count--;

        if (!nxt->count) {              // no word passes here anymore -> prune
            delete nxt;
            cur->child[c] = NULL;
        }
    }

    void del(const string& s) {         // !! only call if s is currently in the trie
        del(root,s,0);
    }

    bool search(const string& s) {      // whole-word lookup (prefix: return cur->count instead)
        Node* cur = root;
        for (char ch : s) {
            int c = ch - baseChar;
            if (cur->child[c] == NULL) return false;
            cur = cur->child[c];
        }
        return cur->isEnd;
    }
};
