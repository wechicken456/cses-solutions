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

const int maxN = 1000;
const int mod = 1e9 + 7;
ll ans = 0;
ll dp[maxN + 1][maxN + 1];
int n;
/*			SLOW SOLUTION USING RECURSION
int path(int row, int col) {
	if (dp[row][col] == -1 || (row > n || col > n)) return 0;
	if (row == n && col == n && dp[n][n] > -1) return 1;
	return (path(row + 1, col) % mod) + (path (row, col + 1) % mod);
}
*/
void solve(){
	char x;
	cin >> n;
	dp[0][1] = 1;
	for (int i = 1; i <= n ; i++){
		for (int j = 1 ; j <= n; j++){
			cin >> x;
			if (x == '*') dp[i][j] = -1;
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (dp[i][j] == -1) continue;
			if (dp[i-1][j] > -1) dp[i][j] += dp[i-1][j];
			if (dp[i][j-1] > -1) dp[i][j] += dp[i][j-1];
			dp[i][j] = dp[i][j] % mod;
		}
	}
	//ans = path(1, 1) % mod;
	//cout << ans << "\n";
	if (dp[n][n] == -1) cout << "0\n";
	else cout << dp[n][n] << "\n";
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


