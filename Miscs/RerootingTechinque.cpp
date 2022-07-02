//rerooting basically states that we answer for one node and then 
// answer the following : what will change if we changed the root from X to Y ?
// we make those changes and continue the recursion order 
// and when done revert those changes
//example problem : https://codeforces.com/contest/1092/problem/F
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vi v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    vector<int> G[n + 55];
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
        G[v].pb(u);
    }
    vector<int> SubtreeSum(n + 55);
    long long res = 0;
    function<void(int, int, int)> calc = [&](int node, int par, int depth)
    {
        res += v[node] * depth;
        SubtreeSum[node] = v[node];
        for (auto i : G[node])
        {
            if (i == par)
                continue;
            calc(i, node, depth + 1);
            SubtreeSum[node] += SubtreeSum[i];
        }
    };
    calc(1, 1, 0);
    long long ans = 0;
    function<void(int, int)> re_rooting = [&](int node, int par)
    {
        ans = max(ans, res);
        for (auto i : G[node])
        {
            if (i == par)
                continue;
            res -= SubtreeSum[i];
            SubtreeSum[node] -= SubtreeSum[i];
            res += SubtreeSum[node];
            SubtreeSum[i] += SubtreeSum[node];
            re_rooting(i, node);
            SubtreeSum[i] -= SubtreeSum[node];
            res -= SubtreeSum[node];
            SubtreeSum[node] += SubtreeSum[i];
            res += SubtreeSum[i];
        }
    };
    re_rooting(1, 1);
    cout << ans << endl;
}
