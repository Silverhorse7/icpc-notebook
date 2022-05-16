//for maximum flow (Dinic)

#define ll long long
#define INF 1000000
struct MaximumHelper {
    struct Edge {
        int to;
        ll remain;
        Edge *flipped;
    };
    const int n;
    vector<map<int, ll>> tmp_graph;
    vector<vector<Edge>> graph;
    vector<vector<Edge *>> level_graph;
    vector<int> dist, q;
    vector<int> dead, vis_list;
    MaximumHelper(int n_) : n(n_), tmp_graph(n), graph(n), level_graph(n), dist(n, -1), dead(n) {
        q.reserve(n);
        vis_list.reserve(2 * n);
    }
    void connect(int i, int j, ll w) {
        tmp_graph[i][j] += w;
        tmp_graph[j][i] += 0;
    }
    void init_graph() {
        for (int i = 0; i < n; ++i)
            graph[i].resize(tmp_graph[i].size());
        vector<int> sz(n);
        for (int i = 0; i < n; ++i) {
            for (const auto &[j, w]: tmp_graph[i]) {
                if (i > j) continue;
                Edge &ij = graph[i][sz[i]++];
                Edge &ji = graph[j][sz[j]++];
                ij.to = j;
                ji.to = i;
                ij.remain = w;
                ji.remain = tmp_graph[j][i];
                ij.flipped = &ji;
                ji.flipped = &ij;
            }
        }
        for (int i = 0; i < n; ++i)
            level_graph[i].reserve(graph[i].size());
    }
    bool init_level_graph() {
        for (int i: q) {
            dist[i] = -1;
            level_graph[i].clear();
        }
        q.clear();
        q.push_back(0);
        dist[0] = 0;
        for (int qq = 0; qq < (int) q.size(); ++qq) {
            int i = q[qq];
            for (const Edge &e: graph[i]) {
                if (!e.remain) continue;
                if (dist[e.to] != -1) continue;
                dist[e.to] = dist[i] + 1;
                q.push_back(e.to);
                if (e.to == n - 1) break;
            }
            if (dist[n - 1] != -1) break;
        }
        if (dist[n - 1] == -1) return false;
        for (int i: q) {
            for (Edge &e: graph[i]) {
                if (!e.remain) continue;
                if (dist[i] >= dist[e.to]) continue;
                if (e.to != n - 1 && dist[e.to] >= dist[n - 1]) continue;
                level_graph[i].push_back(&e);
            }
        }

        return true;
    }
    ll dfs(int cur, ll mn) {
        vis_list.push_back(cur);
        if (cur == n - 1) return INF;
        for (int I = (int) level_graph[cur].size() - 1; I >= 0; --I) {
            Edge *e = level_graph[cur][I];
            if (!e->remain || dead[e->to]) {
                level_graph[cur].pop_back();
                continue;
            }
            ll nxt = min(mn, dfs(e->to, min(e->remain, mn)));
            if (nxt) {
                e->remain -= nxt;
                e->flipped->remain += nxt;
                if (!e->remain) {
                    level_graph[cur].pop_back();
                    if (level_graph[cur].size() == 0)
                        dead[cur] = 1;
                }
                return nxt;
            }
            level_graph[cur].pop_back();
        }
        dead[cur] = 1;
        return 0;
    }
    ll blocking_flow() {
        ll ans = 0;
        ll mn = dfs(0, INF);
        while (mn) {
            ans += mn;
            mn = dfs(0, INF);
        }
        for (int i: vis_list)
            dead[i] = 0;
        vis_list.clear();
        return ans;
    }
    ll solve() {
        init_graph();
        ll ans = 0;
        while (init_level_graph())
            ans += blocking_flow();
        return ans;
    }
};

struct MaximumMatching {
    int n, m;
    MaximumHelper dinics;
    MaximumMatching(int n_, int m_) : n(n_), m(m_), dinics(2 + n + m) {
        for (int i = 0; i < n; ++i)
            dinics.connect(0, i + 1, 1);
        for (int j = 0; j < m; ++j)
            dinics.connect(j + 1 + n, 1 + n + m, 1);
    }
    void connect(int i, int j) {
        dinics.connect(i + 1, j + 1 + n, 1);
    }
    int solve() {
        return (int) dinics.solve();
    }
    vector<array<int, 2>> get_matched() {
        solve();
        vector<array<int, 2>> res;
        for (int i = 0; i < n; ++i) {
            for (auto &e: dinics.graph[i + 1]) {
                if (e.remain) continue;
                if (e.to < 1 + n) continue;
                if (e.to >= 1 + n + m) continue;
                res.push_back({i, e.to - 1 - n});
            }
        }
        return res;
    }
};