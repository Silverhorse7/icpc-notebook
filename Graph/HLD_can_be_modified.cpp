#include "bits/stdc++.h"

using namespace std;

#include <bits/stdc++.h>

using namespace std;

#define ll long long

class segTree {
    vector<ll> tree;
    int n;

public:
    segTree() {}

    segTree(int n, ll init) : tree(4 * n, init), n(n) {}

    void update(int pos, ll val, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = n - 1;
        if (left == right) {
            tree[node] = val;
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid) update(pos, val, node * 2, left, mid);
        else update(pos, val, node * 2 + 1, mid + 1, right);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int l, int r, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = n - 1;
        if (right < l || r < left) return 0;
        if (l <= left && right <= r) return tree[node];
        int mid = (left + right) / 2;
        return query(l, r, node * 2, left, mid) + query(l, r, node * 2 + 1, mid + 1, right);
    }

    void set(int pos, ll val) {
        update(pos, val);
    }

    void add(int pos, ll val) {
        update(pos, query(pos, pos) + val);
    }

    ll get(int pos) {
        return query(pos, pos);
    }

    int getKthOne(int k, int l, int r, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = n - 1;
        if (tree[node] < k || right < l || r < left) return -1;
        if (left == right) return left;
        int mid = (left + right) / 2;
        if (tree[node * 2] >= k) return getKthOne(k, l, r, node * 2, left, mid);
        else return getKthOne(k - tree[node * 2], l, r, node * 2 + 1, mid + 1, right);
    }
};

const int N = 2e5;
int sub[N], depth[N], up[N][22];
vector<vector<int>> g;

int dfs(int node, int par) {
    sub[node] = 1;
    for (auto ch: g[node]) {
        if (ch == par) continue;
        depth[ch] = depth[node] + 1;
        up[ch][0] = node;
        for (int level = 1; level < 22; level++)
            up[ch][level] = up[up[ch][level - 1]][level - 1];
        sub[node] += dfs(ch, node);
    }
    return sub[node];
}

int chain[N], position[N], arr[N], pos, chainID, val[N], chainHead[N], key[N];

void HLD(int node, int par) {
    int hCh = -1, hSz = -1;
    chain[node] = chainID;
    position[node] = pos;
    key[pos] = node;
    arr[pos++] = val[node];
    for (auto ch: g[node]) {
        if (ch == par) continue;
        if (sub[ch] > hSz) {
            hSz = sub[ch];
            hCh = ch;
        }
    }
    if (hCh != -1)
        HLD(hCh, node);
    for (auto ch: g[node]) {
        if (ch == par || ch == hCh) continue;
        chainID++;
        chainHead[chainID] = ch;
        HLD(ch, node);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for (int i = 21; i >= 0; i--) {
        if (k & (1 << i))
            u = up[u][i];
    }
    if (u == v) return u;
    for (int i = 21; i >= 0; i--)
        if (up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];
    return up[u][0];
}

void add_edge(int u, int v) {
    g[u].push_back(v);
}

signed main() {
    int n, q;
    cin >> n >> q;
    g.resize(n);

    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        add_edge(--u, --v);
        add_edge(v, u);
    }
    dfs(0, -1);
    chainHead[0] = 0;
    HLD(0, -1);
    segTree st(n, 0);
    vector<int> color(n + 3);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int v;
            cin >> v;
            v--;
            color[v] ^= 1;
            st.set(position[v], color[v]);
        } else {
            int v;
            cin >> v;
            v--;
            // go up from v to 0
            int u = 0;
            swap(u, v);
            int l = -1, r = -1;
            while (chain[u] != chain[0]) {
                int toGo = up[chainHead[chain[u]]][0];
                if (st.query(position[chainHead[chain[u]]], position[u]))
                    l = st.getKthOne(1l, position[chainHead[chain[u]]], position[u]);
                u = up[chainHead[chain[u]]][0];
            }
            if (st.query(position[chainHead[chain[u]]], position[u]))
                l = st.getKthOne(1l, position[chainHead[chain[u]]], position[u]);
            if (l == -1) cout << -1 << '\n';
            else {
                cout << key[l] + 1 << '\n';
            }
        }
    }
}//
