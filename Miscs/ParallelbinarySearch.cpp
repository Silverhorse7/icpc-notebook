basically instead of doing O( Q * log(n) * n) 
we do it in O(log(n) * (Q+n)) 
//instead of doing binary search for every query , we do them together
// and by specific order (usually by [l,r] order) that way we pretty sure the
//previous query relate to the next query 
//example problem : https://atcoder.jp/contests/agc002/tasks/agc002_d
struct query
{
  int x, y, z, l, r, in;
  void init(int index, int edges)
  {
    cin >> x >> y >> z;
    l = 1, r = edges, in = index; 
  }  
 
  bool operator <(query q)
  {
    return (l + r < q.l + q.r);
  }
};
 
struct DSU
{
    vector<int>par, sz;
    DSU(int n)
    {
        par.resize(n);
        sz.resize(n);
        forn(i, n) sz[i] = 1, par[i] = i;
    }
 
    int get_par(int x)
    {
        if(par[x] == x) return x;
        else return par[x] = get_par(par[x]);
    }
 
    void merge(int u, int v)
    {
        u = get_par(u);
        v = get_par(v);
 
        if(u == v) return;
        if(sz[u] < sz[v]) swap(u, v);
 
        sz[u] += sz[v];
        par[v] = u;
    }
 
    int get_sz(int u)
    {
        return sz[get_par(u)];
    }
    
};
 
int main()
{
 
    IO;
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int n, e; cin >> n >> e; 
 
    vector<pair<int, int>> edges(e);
 
    for(auto &i : edges)
        cin >> i;
 
    int m; cin >> m;
 
    vector<query> q(m);
    forn(i, m)
        q[i].init(i, e);
 
    forn(j, 20)
    {
        sort(all(q));
        int curr_edge = 0;
        DSU graph(n+10);
        for(auto &i : q)
        {
            int mid = (i.l + i.r) >> 1;
            while(curr_edge < mid)
            {
                graph.merge(edges[curr_edge].first, edges[curr_edge].second);
                curr_edge++;
            }
 
            if(i.l == i.r) continue;
            int totalSz = graph.get_sz(i.x) + graph.get_sz(i.y);
            if(graph.get_par(i.x) == graph.get_par(i.y)) totalSz >>= 1;
 
            if(totalSz >= i.z)
                i.r = mid;
            else
                i.l = mid+1;
 
        }
    }
 
    vector<int>ans(m);
 
    for(auto i : q)
        ans[i.in] = i.l;
 
    for(auto i : ans)
        cout << i << el;
 
    return 0;
}
