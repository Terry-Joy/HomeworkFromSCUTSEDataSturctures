#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

template <typename T> class node {
  public:
    T val;
    node *left, *right;
    node(T _val)
        : val(_val)
        , left(nullptr)
        , right(nullptr) {
    }
};

template <typename T> class BinaryTree {
  public:
    using pointer = node<T> *;
    pointer root;

    BinaryTree(int n, int rt, int son[][2])
        : root(nullptr) {
        queue<pointer> q;
        q.push(root = new node<T>(rt));
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (son[tmp->val][0])
                q.push(tmp->left = new node<T>(son[tmp->val][0]));
            if (son[tmp->val][1])
                q.push(tmp->right = new node<T>(son[tmp->val][1]));
        }
    }

    // 6-7
    bool isComplete() const {
        queue<pointer> q;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (tmp->left || tmp->right) {
                if (tmp->left && tmp->right) {
                    q.push(tmp->left);
                    q.push(tmp->right);
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    // 6-8
    bool isSequence() const {
        queue<pointer> q;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (tmp->left) {
                if (tmp->left->val != tmp->val * 2)
                    return false;
                else
                    q.push(tmp->left);
            }
            if (tmp->right) {
                if (tmp->right->val != tmp->val * 2 + 1)
                    return false;
                else
                    q.push(tmp->right);
            }
        }
        return true;
    }

    // 6-9
    bool isHeightBalance() const {
        bool ret = true;
        heightBalance(root, ret);
        return ret;
    }

    static int heightBalance(const pointer &p, bool &isBalance) {
        if (!isBalance) return 0;
        int l = (p->left ? heightBalance(p->left, isBalance) : 0);
        int r = (p->right ? heightBalance(p->right, isBalance) : 0);
        isBalance &= (l == r || (l + 1) == r || (r + 1) == l);
        return max(l, r) + 1;
    }

    // 6-10
    int size() const {
        queue<pointer> q;
        int ret = 0;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            ret++;
            if (tmp->left) q.push(tmp->left);
            if (tmp->right) q.push(tmp->right);
        }
        return ret;
    }

    // 6-11
    int height() const {
        queue<pair<pointer, int>> q;
        int ret = 0;
        q.push({root, 1});
        while (!q.empty()) {
            pair<pointer, int> tmp = q.front();
            q.pop();
            ret = tmp.second;
            if (tmp.first->left) q.push({tmp.first->left, tmp.second + 1});
            if (tmp.first->right) q.push({tmp.first->right, tmp.second + 1});
        }
        return ret;
    }

    // 6-12
    int countLeaf() const {
        queue<pointer> q;
        int ret = 0;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (!tmp->left && !tmp->right) ret++;
            if (tmp->left) q.push(tmp->left);
            if (tmp->right) q.push(tmp->right);
        }
        return ret;
    }

    // 6-13
    BinaryTree(const BinaryTree &src, bool recursion = false)
        : root(nullptr) {
        if (recursion) {
            copy(src.root, root);
        } else {
            queue<pointer const *> s;
            queue<pointer *> t;
            s.push(&(src.root));
            t.push(&root);
            while (!s.empty() && !t.empty()) {
                pointer const *sr = s.front();
                pointer *tg = t.front();
                s.pop();
                t.pop();
                *tg = new node<T>((*sr)->val);
                if ((*sr)->left) {
                    s.push(&((*sr)->left));
                    t.push(&((*tg)->left));
                }
                if ((*sr)->right) {
                    s.push(&((*sr)->right));
                    t.push(&((*tg)->right));
                }
            }
        }
    }

    static void copy(const pointer &src, pointer &tgt) {
        tgt = new node<T>(src->val);
        if (src->left) copy(src->left, tgt->left);
        if (src->right) copy(src->right, tgt->right);
    }

    // 6-16
    void printLeafPath() const {
        cout << "All leaf path:" << endl;
        vector<int> tmp;
        leafPath(root, tmp);
    }

    static void leafPath(const pointer &p, vector<int> &vec) {
        vec.push_back(p->val);
        if (p->left || p->right) {
            if (p->left) leafPath(p->left, vec);
            if (p->right) leafPath(p->right, vec);
        } else {
            for (auto &i : vec)
                cout << i << ' ';
            cout << endl;
        }
        vec.pop_back();
    }

    // 6-17
    string extPreOrder() const {
        string ret;
        extPre(root, ret);
        return ret;
    }

    static void extPre(const pointer &p, string &ret) {
        ret += (p ? to_string(p->val) : "*") + ' ';
        if (p) {
            extPre(p->left, ret);
            extPre(p->right, ret);
        }
    }
};

#define print(var) cout << #var << " = " << var << endl
int son[100][2];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i == 2; i++) {
        cout << "fuck" << i << endl;
    }
    for (int i = 1; i <= n; i++)
        cin >> son[i][0] >> son[i][1];
    BinaryTree<int> tree(10, 1, son);
    print(tree.isComplete());      // 6-7
    print(tree.isSequence());      // 6-8
    print(tree.isHeightBalance()); // 6-9
    print(tree.size());            // 6-10
    print(tree.height());          // 6-11
    print(tree.countLeaf());       // 6-12
    // 6-13
    BinaryTree<int> b(tree, false);
    print(b.size());
    BinaryTree<int> c(tree, true);
    print(c.size());
    tree.printLeafPath();      // 6-16
    print(tree.extPreOrder()); // 6-17
}