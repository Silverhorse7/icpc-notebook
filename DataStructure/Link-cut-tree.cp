/*
 * You are given rooted tree with N weighted nodes numbered from 1 to N. The root of tree is node with number 1. 
 * Your goal is to handle Q queries, each of which can be one of the below three types:

getSum(u) := returns sum of values in nodes in u's subtree.
add(u, x) := adds x to values of every node in u's subtree (including u).
swap(u, v) := swaps whole subtrees of u and v if and only if the subtrees are disjoint.
 */
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

struct Node {
    long long val, summ, oper, num;
    int pri, sz;
    Node *l, *r, *par;

    Node(long long val1, int num1) : num(num1), val(val1), summ(val1), sz(1), oper(0), pri(rand()), l(nullptr),
                                     r(nullptr), par(nullptr) {}
};

vector<int> tour;
vector<int> g[MAXN];
vector<Node *> fst(MAXN, nullptr), lst(MAXN, nullptr);
Node *dd = nullptr;
Node *tmp1, *tmp2, *tmp3, *tmp4, *tmp5;

void dfs(int v, int p) {
    tour.push_back(v);
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to == p) continue;
        dfs(to, v);
    }
    tour.push_back(v);
}

int get_sz(Node *v) {
    if (!v) return 0;
    return v->sz;
}

long long get_summ(Node *v) {
    if (!v) return 0;
    return v->summ;
}

void update(Node *v) {
    if (!v) return;
    v->sz = get_sz(v->l) + get_sz(v->r) + 1;
    v->summ = get_summ(v->l) + get_summ(v->r) + v->val;
    if (v->l) v->l->par = v;
    if (v->r) v->r->par = v;
}

void push(Node *v) {
    if (v->oper == 0) return;
    if (v->l) {
        v->l->oper += v->oper;
        v->l->val += v->oper;
        v->l->summ += v->l->sz * 1ll * v->oper;
    }
    if (v->r) {
        v->r->oper += v->oper;
        v->r->val += v->oper;
        v->r->summ += v->r->sz * 1ll * v->oper;
    }
    v->oper = 0;
    return;
}

void split(Node *root, Node *&l, Node *&r, int k) {
    if (!root) {
        l = r = nullptr;
        return;
    }
    push(root);
    root->par = nullptr;
    if (get_sz(root->l) >= k) {
        split(root->l, l, root->l, k);
        r = root;
        update(r);
    } else {
        split(root->r, root->r, r, k - 1 - get_sz(root->l));
        l = root;
        update(l);
    }
}

void merge(Node *&root, Node *l, Node *r) {
    if (!l || !r) {
        root = l ? l : r;
        return;
    }
    push(l);
    push(r);
    if (l->pri > r->pri) {
        merge(l->r, l->r, r);
        root = l;
    } else {
        merge(r->l, l, r->l);
        root = r;
    }
    update(root);
}

int get_pos(Node *v) {
    int res = get_sz(v->l) + 1;
    while (v->par != nullptr) {
        Node *nxt = v->par;
        if (v == nxt->r) res += get_sz(nxt->l) + 1;
        v = nxt;
    }
    return res;
}

long long Get_summ(int v) {
    int l = get_pos(fst[v]), r = get_pos(lst[v]);
    //cout<<l<<" "<<r<<endl;
    split(dd, tmp1, tmp2, l - 1);
    split(tmp2, tmp2, tmp3, r - l + 1);
    long long res = get_summ(tmp2);
    merge(dd, tmp1, tmp2);
    merge(dd, dd, tmp3);
    return res;
}

void Add(int v, long long val) {
    int l = get_pos(fst[v]), r = get_pos(lst[v]);
    split(dd, tmp1, tmp2, l - 1);
    split(tmp2, tmp2, tmp3, r - l + 1);
    tmp2->oper += val;
    tmp2->val += val;
    tmp2->summ += tmp2->sz * 1ll * val;
    merge(dd, tmp1, tmp2);
    merge(dd, dd, tmp3);
}

void Swap(int u, int v) {
    int l1 = get_pos(fst[u]), r1 = get_pos(lst[u]);
    int l2 = get_pos(fst[v]), r2 = get_pos(lst[v]);
    if (l1 > l2) {
        swap(l1, l2);
        swap(r1, r2);
    }
    if (l2 <= r1) {
        cout << -1 << '\n';
        return;
    }
    l2 -= r1, r2 -= r1;
    split(dd, tmp1, tmp2, l1 - 1);
    split(tmp2, tmp2, tmp3, r1 - l1 + 1);
    split(tmp3, tmp3, tmp4, l2 - 1);
    split(tmp4, tmp4, tmp5, r2 - l2 + 1);
    merge(dd, tmp1, tmp4);
    merge(dd, dd, tmp3);
    merge(dd, dd, tmp2);
    merge(dd, dd, tmp5);
}

void print(Node *root) {
    if (!root) return;
    print(root->l);
    cout << root->num << " ";
    print(root->r);
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1, -1);
    for (int i = 0; i < tour.size(); i++) {
        Node *nw = new Node(w[tour[i]], tour[i]);
        merge(dd, dd, nw);
        if (fst[tour[i]] == nullptr) fst[tour[i]] = nw; else lst[tour[i]] = nw;
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u;
            cin >> u;
            cout << Get_summ(u) / 2 << '\n';
        } else if (type == 2) {
            int u, x;
            cin >> u >> x;
            Add(u, x);
        } else if (type == 3) {
            int u, v;
            cin >> u >> v;
            Swap(u, v);
        }
        //print(dd); cout<<endl;
    }

    return 0;
}
