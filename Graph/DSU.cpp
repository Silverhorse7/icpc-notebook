
struct DSU {
    int n;
    int N; // give it a value   
 vector<int>par;
 
    void init() {
        par.resize(N);
        iota(all(par),0);
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