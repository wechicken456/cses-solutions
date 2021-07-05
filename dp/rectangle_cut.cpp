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

const int maxN = 500;
const int maxX = 500;
int n, m,a,b,x;
int ans = 0;
int dp[maxN+1][maxX+1];

void solve(){
	cin >> n >> m;
	int smaller = min(n,m), bigger = max(n, m);
	for (int i = 1; i <= smaller; i++){
		dp[i][1] = i - 1;
	}
	for (int i = 1; i <= bigger; i++){
		dp[1][i] = i - 1;
	}
	// NOTE: simply cutting into 2 rectangles: width x width and width x (height - width) doesn't work.
	for (int i = 2; i <= smaller; i++){
		for (int j = 2; j <= bigger; j++){
			if (i == j) dp[i][i] = 0;
			else {
				dp[i][j] = 1e9;
				for (int k = 1 ; k < j; k++){			// cut horizontally
					dp[i][j] = min(dp[i][j], dp[i][j-k] + dp[i][k] + 1);
				}
				for (int k = 1; k < i ; k++){			// cut vertically 
					dp[i][j] = min(dp[i][j], dp[k][j] + dp[i-k][j] + 1);
				}
			}
		}
	}
	cout << dp[smaller][bigger];
}

int main(){
	solve();
}


