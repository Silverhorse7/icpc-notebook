#include<bits/stdc++.h>
using namespace std;
struct DSU {
    int n;
 vector<int>par;
    void init(int N) {
        par.resize(N);
        iota(par.begin(),par.end(),0);
    }
    int get(int x) {
        if (par[x] == x) return x;
        return par[x] = get(par[x]);
    }
    void unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return;
        par[x] = y;
        return;
    }
    bool connected(int u ,int v){
        return get(u)==get(v);
    }
};
