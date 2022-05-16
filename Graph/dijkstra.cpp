class Dijkstra {
public:
    struct Edge {
        long long to, cost;
    };
    vector<ll> d;
    vector<vector<Edge>> G;

    Dijkstra(int n) {
        G = vector<vector<Edge>>(n);
        d = vector<ll>(n, 1e18);
    }

    void add_edge(ll from, ll to, ll cost) {
        Edge e = {to, cost};
        G[from].push_back(e);
    }

    void dijkstra(ll s) {
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> que;
        d[s] = 0;
        que.push(pair<ll, ll>(0, s));

        while (!que.empty()) {
            pair<ll, ll> p = que.top();
            que.pop();
            ll v = p.second;
            if (d[v] < p.first) continue;
            for (int i = 0; i < G[v].size(); i++) {
                Edge e = G[v][i];
                if (d[e.to] > d[v] + e.cost) {
                    d[e.to] = d[v] + e.cost;
                    que.push(pair<ll, ll>(d[e.to], e.to));
                }
            }
        }
    }
};

int BFS(int &start, int &end ,vector<vector<int>>&adj,int &n){
    queue<int>q;
    vector<int>dist(n+2);
    q.push(start);
    dist[start]=0;
    while(!q.empty()){
        int father = q.front();
        q.pop();
        for(auto child : adj[father]){
            if(dist[child] == 0 and child != 1){
                dist[child]= dist[father] + 1;
                q.push(child);
            }
        }
    }
    return dist[end]+1; // because we started with depth 0
}