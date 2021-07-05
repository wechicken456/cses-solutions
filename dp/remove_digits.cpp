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

const int maxN = 1e6;
int dp[maxN + 1];
void solve(){
	/* 		permutations
	vector<ll>arr; // need to add contents to arr 
	do {
		// process permutation here
	} while (next_permutation(arr.begin(), arr.end()));
	*/
	int n;
	scanf("%d", &n);
	for (int i = 1 ; i <= n; i++){
		dp[i] = 1e9;
		int cur = i ; 
		while(cur > 0) {
			dp[i] = min(dp[i], dp[i - cur % 10] + 1);
			cur /= 10;
		}
	}
	cout << dp[n];
}

int main(){
	/*ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--){
		solve();
	}*/
	solve();
}


