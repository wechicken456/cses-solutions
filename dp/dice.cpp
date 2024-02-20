#include<bits/stdc++.h>
#include<vector>

using namespace std;
#define ll long long

const ll maxN = 1e9+1;
const ll m = 1e9 + 7;

ll n;
int main(){
	cin >> n;
	vector<ll>dp(n+1, 0);
	dp[0] = 1;
	for (ll i = 1 ; i <= n; i++){
		for (ll j = 1; j <= 6; j++){
			if (i - j >= 0) {
				dp[i] += dp[i-j];
				dp[i] %= m;
			}
		}
	}
	cout << dp[n] << "\n";
}
