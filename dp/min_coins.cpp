#include<bits/stdc++.h>
#include<set>
#include<stdio.h>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
#include<math.h>
#include<cmath>
#include<fstream>

#define ll long long
#define ull unsigned long long
#define pb push_back

using namespace std;

ull power(ll x, ull y) {
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
        return power(x, y / 2) * power(x, y / 2);
    else
        return x * power(x, y / 2) * power(x, y / 2);
}
 
ll my_ceil(ll a, ll b) {
	return (a/b) + ( (a%b)!=0 );
}

void solve(){
	/* 		permutations
	vector<ll>arr; // need to add contents to arr 
	do {
		// process permutation here
	} while (next_permutation(arr.begin(), arr.end()));
	*/
	int n,x;
	cin >> n >> x;
	vector<int>coins(n);
	for (int i = 0 ; i < n; i++){
		cin >> coins[i];
	}
	vector<int>dp(x+1);
	dp[0] = 0;
	for (int i = 1; i <= x; i++){
		dp[i] = 1e9 + 1;
		for (auto &c : coins){
			if (i - c >= 0) {
				dp[i] = min(dp[i], dp[i-c] + 1);
			}
		}
	}
	if (dp[x] > 1e9) cout << -1 << "\n";
	else cout << dp[x] << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	/*int T;
	cin >> T;
	while (T--){
		solve();
	}*/
	solve();
}


