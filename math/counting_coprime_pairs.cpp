// https://cses.fi/problemset/task/2417/
#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define vb vector<bool>

using namespace std;

// factors[x][s]: vector of factors of x where each factor is composed of s primes.
vector<vector<vector<int>>>factors((int)1e6+1, vector<vector<int>>(8));
vector<int>cnt((int)1e6+1, 0);

// factor into distinct prime factors
void prime_factorize(int x) {
	if (factors[x][1].size()) return; // we have already factor'ed x before
	
	int original_x = x;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			factors[original_x][1].pb(i);
		}
		while (x % i == 0) x /= i;
	}
	if (x != 1) {
		factors[original_x][1].pb(x);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;
	vector<int>a(n);
	for (int &x : a) {
		cin >> x;
	}
	
	ll ans = 0;
	for (int i = 0 ; i < n; i++) {
		int x = a[i];
		int s = factors[x][1].size();
		bool first_time = false;
		if (s == 0) {	// first time we factorize x
			prime_factorize(x);
			first_time = true;
		}
		s = factors[x][1].size();
		vector<int>&f = factors[x][1];
		
		// take the list of prime factors, then for each subset,
		// increment the count of the its product
		for (int j = 1; j < (1 << s); j++) {
			int prod = 1;
			int subset_size = 0;
			for (int b = 0; b < s; b++) {
				if (j & (1 << b)) {
					subset_size++;
					prod *= f[b];
				}
			}
			cnt[prod]++;
			if (first_time && subset_size > 1) factors[x][subset_size].pb(prod);
		}

		// loop through all subsets of factors of x to find 
		// the number of elements that are NOT coprime with x
		// using PIE: https://en.wikipedia.org/wiki/Inclusion–exclusion_principle#Formula
		ll not_coprime = 0;
		for (int subset_size = 1 ; subset_size <= 7; subset_size++) {
			for (int j = 0 ; j < factors[x][subset_size].size(); j++) {
				if (subset_size % 2 == 1) {
					not_coprime += cnt[factors[x][subset_size][j]];
				}
				else {
					not_coprime -= cnt[factors[x][subset_size][j]];
				}
			}
		}
		if (x > 1) not_coprime -= 1;
		//cout << not_coprime << "\n";
		ans += i - not_coprime;
	}
	cout << ans << "\n";
	return 0;
}


