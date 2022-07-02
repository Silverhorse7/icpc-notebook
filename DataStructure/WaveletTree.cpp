#include <bits/stdc++.h>
using namespace std;
#define fo(i,n) for(i=0;i<n;i++)
#define ll long long

#define pb push_back
#define mp make_pair


typedef pair<int, int>	pii;
typedef pair<ll, ll>	pl;
typedef vector<int>		vi;

const int N = 3e5, M = N;
//=======================
const int MAX = 1e6;

int a[N];
struct wavelet_tree
{
#define vi vector<int>
#define pb push_back
    int lo, hi;
    wavelet_tree *l, *r;
    vi b;
    vi c; // c holds the prefix sum of elements

    //nos are in range [x,y]
    //array indices are [from, to)
    wavelet_tree(int *from, int *to, int x, int y)
    {
        lo = x, hi = y;
        if( from >= to)
            return;
        if( hi == lo )
        {
            b.reserve(to-from+1);
            b.pb(0);
            c.reserve(to-from+1);
            c.pb(0);
            for(auto it = from; it != to; it++)
            {
                b.pb(b.back() + 1);
                c.pb(c.back()+*it);
            }
            return ;
        }
        int mid = (lo+hi)/2;
        auto f = [mid](int x)
        {
            return x <= mid;
        };
        b.reserve(to-from+1);
        b.pb(0);
        c.reserve(to-from+1);
        c.pb(0);
        for(auto it = from; it != to; it++)
        {
            b.pb(b.back() + f(*it));
            c.pb(c.back() + *it);
        }
        //see how lambda function is used here
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid+1, hi);
    }

    // swap a[i] with a[i+1]  , if a[i]!=a[i+1] call swapadjacent(i)
    void swapadjacent(int i)
    {
        if(lo == hi)
            return ;
        b[i]= b[i-1] + b[i+1] - b[i];
        c[i] = c[i-1] + c[i+1] - c[i];
        if( b[i+1]-b[i] == b[i] - b[i-1])
        {
            if(b[i]-b[i-1])
                return this->l->swapadjacent(b[i]);
            else
                return this->r->swapadjacent(i-b[i]);
        }
        else
            return ;
    }

    //kth smallest element in [l, r]
    int kth(int l, int r, int k)
    {
        if(l > r)
            return 0;
        if(lo == hi)
            return lo;
        int inLeft = b[r] - b[l-1];
        int lb = b[l-1]; //amt of nos in first (l-1) nos that go in left
        int rb = b[r]; //amt of nos in first (r) nos that go in left
        if(k <= inLeft)
            return this->l->kth(lb+1, rb, k);
        return this->r->kth(l-lb, r-rb, k-inLeft);
    }

    //count of nos in [l, r] Less than or equal to k
    int LTE(int l, int r, int k)
    {
        if(l > r or k < lo)
            return 0;
        if(hi <= k)
            return r - l + 1;
        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
    }

    //count of nos in [l, r] equal to k
    int count(int l, int r, int k)
    {
        if(l > r or k < lo or k > hi)
            return 0;
        if(lo == hi)
            return r - l + 1;
        int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
        if(k <= mid)
            return this->l->count(lb+1, rb, k);
        return this->r->count(l-lb, r-rb, k);
    }

    //sum of nos in [l ,r] less than or equal to k
    int sumk(int l, int r, int k)
    {
        if(l > r or k < lo)
            return 0;
        if(hi <= k)
            return c[r] - c[l-1];
        int lb = b[l-1], rb = b[r];
        return this->l->sumk(lb+1, rb, k) + this->r->sumk(l-lb, r-rb, k);
    }

    ~wavelet_tree()
    {
        delete l;
        delete r;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
    int i,n,k,j,q,l,r;
    cin >> n;
    fo(i, n) cin >> a[i+1];
    wavelet_tree T(a+1, a+n+1, 1, MAX);
    cin >> q;
    while(q--)
    {
        int x;
        cin >> x;
        cin >> l >> r >> k;
        if(x == 0)
        {
            //kth smallest
            cout << "Kth smallest: ";
            cout << T.kth(l, r, k) << endl;
        }
        if(x == 1)
        {
            //less than or equal to K
            cout << "LTE: ";
            cout << T.LTE(l, r, k) << endl;
        }
        if(x == 2)
        {
            //count occurence of K in [l, r]
            cout << "Occurence of K: ";
            cout << T.count(l, r, k) << endl;
        }
        if(x == 3)
        {
            //sum of elements less than or equal to K in [l, r]
            cout << "Sum: ";
            cout << T.sumk(l, r, k) << endl;
        }

    }
    return 0;
}