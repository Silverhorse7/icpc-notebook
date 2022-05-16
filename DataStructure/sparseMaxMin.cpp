#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 6e18;
const ll mod = 1e9+7;
const int N = 2e5 + 5;
const int M = 1e6 + 5;
const int sq = 448;

ll cur, freq[M];
vector<ll> arr(N);

struct query {
    int l, r, i;
    query(int lq, int rq, int iq) {
        l = lq, r = rq, i = iq;
    }
    bool operator < (const query &q) {
        if(q.l/sq != l/sq)
            return l/sq < q.l/sq;
        return r < q.r;
    }
};
 
void add(int i) {
    
    cur+=arr[i]*(2*freq[arr[i]]+1);
    freq[arr[i]]++;
}
 
void remove(int i) {
    
    cur-=arr[i]*(2*freq[arr[i]]-1);
    freq[arr[i]]--;
}
 
void testCase() {

    int n, q, l, r;
    vector<query> queries;

    cin >> n >> q;

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    for (int i = 0; i < q; i++) {
        
        cin >> l >> r;
        queries.push_back({l-1, r-1, i});
    }

    vector<ll> ans(q);
    sort(queries.begin(), queries.end());
    int curL = 1, curR = 0;
    for(auto &j : queries) {
        int l = j.l, r = j.r, i = j.i;
        while(curL > l)
            add(--curL);
        while(curR < r)
            add(++curR);
        while(curL < l)
            remove(curL++);
        while(curR > r)
            remove(curR--);
        ans[i] = cur;
    }

    for (auto i : ans)
        cout << i << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 1;

   // cin >> T;

    while (T--)
        testCase();

    return 0;
}