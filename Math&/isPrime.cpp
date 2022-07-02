int isPrime(long long number) {

  if (number == 0 || number == 1 || (number % 2 == 0 && number > 2)) {
    return 0;
  }

  else {
    for (long long i=3; i <= (long long)sqrt(number)+1; i++) {
      if (number % i == 0) {
        return 0;
      }
    }
    return 1;
  }
}
const int MAXN = 1e7+3;
const int N = 1e5 + 2;
int spf[MAXN];
bool mp[MAXN];
int a[N];
int i, j;
 
void sieve() {
    bool jojo = 0;
    for (i = 2; i < MAXN; i++) {
        if (spf[i] == 0) {
            mp[i] = jojo;
            jojo ^= 1;
            spf[i] = i;
            for (j = i; j < MAXN; j += i)
                spf[j] = i;
        }
    }
}

const int N = 1e6 + 5;
int pf[N];
 
void pre() { //call pre at the beginning (in main)
	memset(pf, -1, sizeof(pf));
	for (int i = 2; i < N; i++)
		if (pf[i] == -1) {
			for (int j = i; j < N; j += i) pf[j] = i;
		}
}
 
vector<pair<int, int>> get_pf(int n) { // first : prime , second : power
	vector<pair<int, int>> r;
	int c = n;
	while (c > 1) {
		int v = pf[c];
		r.emplace_back(v, 0);
		while (c % v == 0) r.back().second++, c /= v;
	}
	return r;
}

for (int i = 1; i <= sqrt(n); i++) {
  if (n % i == 0) {
    divs.push_back(i);
    if (n / i != i)
      divs.push_back(n / i);
  }
}
