//TO OPEN FILES 
    freopen("cowcode.in", "r", stdin);
    freopen("cowcode.out", "w", stdout);

//FAST INPUT : 
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

 //Spares table : 
 void buildSparseTable(int arr[], int n)
{
    // Initialize M for the intervals with length 1
    for (int i = 0; i < n; i++)
        lookup[i][0] = arr[i];
 
    // Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
 
        // Compute minimum value for all intervals with
        // size 2^j
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
 
            // For arr[2][10], we compare arr[lookup[0][7]]
            // and arr[lookup[3][10]]
            if (lookup[i][j - 1] <
                        lookup[i + (1 << (j - 1))][j - 1])
                lookup[i][j] = lookup[i][j - 1];
            else
                lookup[i][j] =
                         lookup[i + (1 << (j - 1))][j - 1];
        }
    }
}
//MODIFIED SPARSE TABLE : 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, Q;
    cin >> N >> Q;
 
    vector<int> A(N);
    for (auto &x : A)
        cin >> x;
 
    vector<int> lg(N + 1); // lg[i] = log2(i)
    lg[1] = 0;
    for (int i = 2; i <= N; i++)
        lg[i] = lg[i / 2] + 1;
 
    // sparse[i][j] : Minimum value in the interval [j, j + 2^i - 1]
    vector sparse(lg[N] + 1, vector<int>(N));
 
    for (int j = 0; j < N; j++)
        sparse[0][j] = A[j];
 
    for (int i = 1; i <= lg[N]; i++)
        for (int j = 0; j + (1 << i) - 1 < N; j++) // (1 << x) = 2^x
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
 
    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
 
        int i = lg[r - l + 1];
        cout << min(sparse[i][l], sparse[i][r - (1 << i) + 1]) << "\n";
    }
}
//SPF : 
void manipulated_seive(int N)
{
    // 0 and 1 are not prime
    isprime[0] = isprime[1] = false ;
  
    // Fill rest of the entries
    for (long long int i=2; i<N ; i++)
    {
        if (isprime[i])
        {
            // put i into prime[] vector
            prime.push_back(i);
            SPF[i] = i;
        }
  
        // Remove all multiples of  i*prime[j] which are
        // not prime by making isPrime[i*prime[j]] = false
        // and put smallest prime factor of i*Prime[j] as prime[j]
        // [ for exp :let  i = 5 , j = 0 , prime[j] = 2 [ i*prime[j] = 10 ]
        // so smallest prime factor of '10' is '2' that is prime[j] ]
        // this loop run only one time for number which are not prime
        for (long long int j=0;
             j < (int)prime.size() &&
             i*prime[j] < N && prime[j] <= SPF[i];
             j++)
        {
            isprime[i*prime[j]]=false;
  
            // put smallest prime factor of i*prime[j]
            SPF[i*prime[j]] = prime[j] ;
        }
    }
}
//Ordered Set : 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
//order of key 

//DSU : 
const int N = 1100;
struct dsu {
    int n;
    vector<int>par;
    vector<int>sz;
    void init() {
        par.resize(N);
        sz.resize(N,1);
        iota(all(par),0);
    }
    int get_par(int x) {
        if (par[x] == x) return x;
        return par[x] = get_par(par[x]);
    }
    void merge(int x, int y) {
        x = get_par(x);
        y = get_par(y);
        if (x == y) return;
        if(sz[x]>sz[y])swap(x,y);
        par[x] = y;
        sz[y]+=sz[x];
        return;
    }
};
Problem C : Dsu 
const int N = 2e5 + 1;
const int MOD = 1e9+7;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
vector<int> par,points,extra,siz;
ll getpoint(ll x){
    return (par[x] == x ? points[x] : points[x] - extra[x] + getpoint(par[x]));
}
int findpar(int x){
    return (par[x] == x ? x : findpar(par[x]));
}
void unite(ll a,ll b){
    a = findpar(a);
    b = findpar(b);
    if(siz[a] < siz[b])
        swap(a,b);
    if(a != b){
        par[b] = a;
        siz[a] += siz[b];
        int x = points[a];
        extra[b] = x;
    }
}
int main(){
    debugMode();
    ll n,m,a,b;cin>>n>>m;
    par.resize(n + 1);
    siz.resize(n + 1,1);
    extra.resize(n + 1);
    points.resize(n + 1);
    iota(par.begin(),par.end(),0);
    string s;
    for(int i=0;i<m;i++){
        cin>>s;
        if(s == "join"){
            cin>>a>>b;
            unite(a,b);
        }else if(s == "add"){
            cin>>a>>b;
            a = findpar(a);
            points[a] += b;
        }else{
            cin>>a;
            cout<<getpoint(a)<<endl;
        }
    }
    return 0;
}

//Prefix sum 2d : 
void prefixSum2D(int a[][C])
{
    int psa[R][C];
    psa[0][0] = a[0][0];
 
    // Filling first row and first column
    for (int i = 1; i < C; i++)
        psa[0][i] = psa[0][i - 1] + a[0][i];
    for (int i = 1; i < R; i++)
        psa[i][0] = psa[i - 1][0] + a[i][0];
 
    // updating the values in the cells
    // as per the general formula
    for (int i = 1; i < R; i++) {
        for (int j = 1; j < C; j++)
 
            // values in the cells of new
            // array are updated
            psa[i][j] = psa[i - 1][j] + psa[i][j - 1]
                        - psa[i - 1][j - 1] + a[i][j];
    }
 
    // displaying the values of the new array
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++)
            cout << psa[i][j] << " ";
        cout << "\n";
    }
}
//Prime number : 
bool isPrimeNumber( long long n) {
	    if (n <= 1)
	        return false;
	    if (n <= 3)
	        return true;
	    if (n % 2 == 0 || n % 3 == 0)
	        return false;
	    for (int i = 5; i * i <= n; i = i + 6)
	        if (n % i == 0 || n % (i + 2) == 0)
	            return false;
	    return true;
}
//LCM : 
long long lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}
//Submatrix sum : 
int findSubmatrixSum(int mat[M][N], int p, int q, int r, int s)
{
    int sum[M][N];
    sum[0][0] = mat[0][0];
    for (int j = 1; j < N; j++)
        sum[0][j] = mat[0][j] + sum[0][j - 1];

    for (int i = 1; i < M; i++)
        sum[i][0] = mat[i][0] + sum[i - 1][0];
    for (int i = 1; i < M; i++)
    {
        for (int j = 1; j < N; j++)
        {
            sum[i][j] = mat[i][j] + sum[i - 1][j] + sum[i][j - 1]
                - sum[i - 1][j - 1];
        }
    }
    int total = sum[r][s];
 
    if (q - 1 >= 0)
        total -= sum[r][q - 1];
 
    if (p - 1 >= 0)
        total -= sum[p - 1][s];
 
    if (p - 1 >= 0 && q - 1 >= 0)
        total += sum[p - 1][q - 1];
 
    return total;
}
//nCr : 
ll comb(ll n, ll r)//nCr
{
	ll top = 1;
	ll bot = 1;
	if (n - r > r)
	{
		r = n - r;
	}
	if (r != 0)
	{
		while (r) {
			top *= n;
			bot *= r;
			ll m = gcd(top, bot);
			top /= m;
			bot /= m;
			n--;
			r--;
		}
	}
	else
		top = 1;
	return top;
}
//fast power : 
ull fpow(ull base, ull exp) { 
    ull result = 1;
    while (exp > 0) {
        if (exp & 1) result = (static_cast<ull>(result * base));
        base = (static_cast<ull>(base * base));
        exp >>= 1;
    }
    return result;
}
//Pascal 
	ll pas[101][101];
    pas[0][0]=1;
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<=n; j++)
        {
            pas[i][j]=pas[i-1][j]+pas[i-1][j-1];
        }
    }
int N;
int fact[N];
void create_fact() {
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= M;
	}
}

//dijkstra on 2dgrid  :
int n, m;
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int N = 1e3 + 5;

bool valid(int x, int y) {
    return(x >= 0 and y >= 0 and x < n and y < m);
}
ll dijkstra(vector<vector<int>>& arr) {//grid dijkstra
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>>pq;
    pq.push({ arr[0][0],{0,0} });//changable 
    vector<vector<int>>dist(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = '?';//changable to any large value 
        }
    }
    while (!pq.empty()) {
        int curcost = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();
        if (dist[x][y] != curcost)continue;
        for (int i = 0; i < 4; i++) {//changable too 
            int newx = dx[i] + x;
            int newy = dy[i] + y;
            if (valid(newx, newy) and dist[newx][newy] > curcost + arr[newx][newy]) {
                dist[newx][newy] = curcost + arr[newx][newy];
                pq.push({ dist[newx][newy],{newx,newy} });
            }
        }
    }
    return dist[n - 1][m - 1];
}

//LCS
    string a, b;
    cin >> a >> b;
    vector<vector<int>>dp(a.size()+1, vector<int>(b.size()+1, 0));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (a[i] == b[j]) {
                max_self(dp[i + 1][j + 1], dp[i][j] + 1);
            }
            max_self(dp[i + 1][j], dp[i][j]);
            max_self(dp[i][j + 1], dp[i][j]);
        }
    }
    int ans = 0;
    for (auto ele : dp) {
        for (auto lee : ele) {
            ans = max(ans, lee);
        }
    }
    cout << ans << endl;
    //longest palindrome substring 

 
void findLongestPalindromicString(string text)//substring
{
    int N = text.size();
    if (N == 0)
        return;
    N = 2 * N + 1; //Position count
    int L[N]; //LPS Length Array
    L[0] = 0;
    L[1] = 1;
    int C = 1; //centerPosition
    int R = 2; //centerRightPosition
    int i = 0; //currentRightPosition
    int iMirror; //currentLeftPosition
    int maxLPSLength = 0;
    int maxLPSCenterPosition = 0;
    int start = -1;
    int end = -1;
    int diff = -1;

    //Uncomment it to print LPS Length array
    //printf("%d %d ", L[0], L[1]);
    for (i = 2; i < N; i++)
    {
        //get currentLeftPosition iMirror for currentRightPosition i
        iMirror = 2 * C - i;
        L[i] = 0;
        diff = R - i;
        //If currentRightPosition i is within centerRightPosition R
        if (diff > 0)
            L[i] = min(L[iMirror], diff);

        //Attempt to expand palindrome centered at currentRightPosition i
        //Here for odd positions, we compare characters and
        //if match then increment LPS Length by ONE
        //If even position, we just increment LPS by ONE without
        //any character comparison
        while (((i + L[i]) < N && (i - L[i]) > 0) &&
            (((i + L[i] + 1) % 2 == 0) ||
                (text[(i + L[i] + 1) / 2] == text[(i - L[i] - 1) / 2])))
        {
            L[i]++;
        }

        if (L[i] > maxLPSLength) // Track maxLPSLength
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }

        //If palindrome centered at currentRightPosition i
        //expand beyond centerRightPosition R,
        //adjust centerPosition C based on expanded palindrome.
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
        //Uncomment it to print LPS Length array
        //printf("%d ", L[i]);
    }
    //printf("\n");
    start = (maxLPSCenterPosition - maxLPSLength) / 2;
    end = start + maxLPSLength - 1;
    printf("LPS of string is %s : ", text);
    for (i = start; i <= end; i++)
        printf("%c", text[i]);
    printf("\n");
}


int maxSubArraySum(int a[], int size)
{
    int max_so_far = INT_MIN, max_ending_here = 0,
       start =0, end = 0, s=0;
 
    for (int i=0; i< size; i++ )
    {
        max_ending_here += a[i];
 
        if (max_so_far < max_ending_here)
        {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
 
        if (max_ending_here < 0)
        {
            max_ending_here = 0;
            s = i + 1;
        }
    }
    cout << "Maximum contiguous sum is "
        << max_so_far << endl;
    cout << "Starting index "<< start
        << endl << "Ending index "<< end << endl;
}	

// Function to return the maximum length of
// strictly increasing subarray after
// removing atmost one element
int maxIncSubarr(vector<int>&a)
{
	int n=  a.size();
    // Create two arrays pre and pos
    vector<int>pre(n);
    vector<int>pos(n);
    pre[0] = 1;
    pos[n - 1] = 1;
    int l = 0;
 
    // Find out the contribution of the current
    // element in array[0, i] and update pre[i]
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i - 1])
            pre[i] = pre[i - 1] + 1;
        else
            pre[i] = 1;
    }
 
    // Find out the contribution of the current
    // element in array[N - 1, i] and update pos[i]
    l = 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] < a[i + 1])
            pos[i] = pos[i + 1] + 1;
        else
            pos[i] = 1;
    }
 
    // Calculate the maximum length of the
    // stricly increasing subarray without
    // removing any element
    int ans = 0;
    l = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i - 1])
            l++;
        else
            l = 1;
        ans = max(ans, l);
    }
 
    // Calculate the maximum length of the
    // strictly increasing subarray after
    // removing the current element
    for (int i = 1; i <= n - 2; i++) {
        if (a[i - 1] < a[i + 1])
            ans = max(pre[i - 1] + pos[i + 1], ans);
    }
 
    return ans;
}
