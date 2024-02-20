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
#define FOR(i, n) for (int i = 0 ; i < n; i++)

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

const int maxN = 5000;
const int maxM = 5000;
int n, m,x;
int dp[maxN+1][maxM+1];

/*
- If we can transform s[1..i] to t[1..j-1] in k operations, then we can simply add t[j] afterwards to get t[1..j] in k+1 operations (insertion).
- If we can transform s[1..i-1] to t[1..j] in k operations, then we can remove s[i] and then do the same transformation, for a total of k+1 operations (deletion).
- If we can transform s[1..i-1] to t[1..j-1] in k operations, then we can do the same to s[1..i], and exchange the original s[i] for t[j] afterwards, for a total of k+1 operations (substitution).
*/

void solve(){
	string s1,s2;
	cin >> s1 >> s2;
	int l1 = s1.length();
	int l2 = s2.length();
	for (int i = 0; i <= l1; i++){		// number of columns is l1
		dp[0][i] = i;
	}
	for (int i = 0; i <= l2; i++){		// number of rows is l2
		dp[i][0] = i;
	}
	for (int i = 1; i <= l2; i++){
		for (int j = 1; j <= l1; j++){
			int cost = 0;
			if (s2[i-1] != s1[j-1]) cost = 1;
			dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1);
			dp[i][j] = min(dp[i][j], dp[i-1][j-1] + cost);
			// 2 lines here are similar to dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + cost);
		}
	}
	cout << dp[l2][l1];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}


